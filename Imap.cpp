/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imap.cpp
 * Author: ckarner
 * 
 * Created on November 23, 2015, 12:25 PM
 */

#include "Imap.h"
#include <QString>
#include <QChar>
#include <QTextStream>
#include <QDebug>
#include <QSslSocket>
#include <QRegularExpression>
#include "Mail.h"
#include <QLocale>
#include "Base64.h"
#include "DataRepository.h"


QString Imap::stringFromImap(QString input) {
    return input.replace("&AOQ-", "ä")
            .replace("&APY-", "ö")
            .replace("&APw-", "ü")
            .replace("&AMQ-", "Ä")
            .replace("&ARN-", "Ö")
            .replace("&ANw-", "Ü")
            .replace("&AN8-", "ß");
}

QString Imap::stringToImap(QString input) {
    return input.replace("ä", "&AOQ-")
            .replace("ö", "&APY-")
            .replace("ü", "&APw-")
            .replace("Ä", "&AMQ-")
            .replace("Ö", "&ARN-")
            .replace("Ü", "&ANw-")
            .replace("ß", "&AN8-");
}


unsigned short int Imap::tagPrefix = 65;
unsigned short int Imap::tagNumber = 0;

QString Imap::nextTag() {
    if (tagNumber == 999) {
        if (tagPrefix < 90) {
            tagPrefix++;
        }
        else {
            tagPrefix = 65;
        }
        tagNumber = 0;
    }
    
    QString tmpTag = (char)tagPrefix + QString("%1").arg(tagNumber, 3, 10, QChar('0')) + " ";
    tagNumber++;
    return tmpTag;
}


QString Imap::buildPath(Directory* dir) {
    if (dir->getParentDirectory() == 0) {
        return dir->getName();
    }
    else {
        return buildPath(dir->getParentDirectory()) + "/" + dir->getName();
    }
}


Directory* Imap::getDirectoryByPath(QString path, QList<Directory*> list) {
    QString tldDir = path;
    QString newPath = "";
    
    if (tldDir.contains("/")) {
        tldDir.truncate(tldDir.indexOf("/"));
        newPath = path.mid(path.indexOf("/") + 1);
    }
    
    foreach (Directory* dir, list) {
        if (dir->getName() == tldDir) {
            if (newPath == "") {
                return dir;
            }
            else {
                return getDirectoryByPath(newPath, dir->getSubDirectories());
            }
        }
    }
    
    return 0;
}


Imap::Imap(const Imap& imap) : QObject(imap.parent()) {
    directoryListReady = false;
    this->queue = imap.queue;
    this->queue.setInterval(imap.queue.getInterval());
};

Imap::Imap(DataRepository *repository) {    
    this->repository = repository;
    
    initialize();
}

void Imap::initialize() {
    directoryId = 0;
    indicator = 0;
    currentDir = 0;
    currentCommand = DEFAULT;
    textIncoming = false;
    connected = false;
    
    responsePattern.append("[A-Z][0-9]{3} OK .*");
    responsePattern.append("[A-Z][0-9]{3} NO .*");
    responsePattern.append("[A-Z][0-9]{3} BAD .*");
    
    QObject::connect(this, SIGNAL(pipeReady()), &queue, SLOT(pipeReady()));
    QObject::connect(&queue, SIGNAL(nextCommand(QString, Directory*)), this, SLOT(sendCommand(QString, Directory*)));
    
    unsigned int timeout =  repository->getSettings()->getImapTimeout();
    
    setTimeout(10);
}

Imap::~Imap() {
    if (isConnected()) {
        logout();
    }
}


void Imap::setCurrentCommand(QString cmd) {
    if (cmd.startsWith("LOGIN ")) {
        currentCommand = LOGIN;
    }
    else if (cmd.startsWith("LIST ")) {
        currentCommand = LIST;
    }
    else if (cmd.startsWith("SELECT ")) {
        currentCommand = SELECT;
    }
    else if (cmd.startsWith("FETCH ") || cmd.startsWith("UID FETCH ")) {
        currentCommand = FETCH;
    }
    else if (cmd.startsWith("NOOP")) {
        currentCommand = NOOP;
    }
    else if (cmd.startsWith("UID STORE ")) {
        currentCommand = STORE;
    }
    else if (cmd.startsWith("EXPUNGE")) {
        currentCommand = EXPUNGE;
    }
    else if (cmd.startsWith("LOGOUT")) {
        currentCommand = LOGOUT;
    }
}


void Imap::sendCommand(QString cmd, Directory* dir) {
    setCurrentCommand(cmd);
    currentDir = dir;
    QString command = nextTag() + cmd + "\r\n";
    qDebug() << "> " << command;
    
    if (currentCommand == FETCH) {
        dir->clearMail();
    }
    
    *stream << command;
    stream->flush();
    
    printLine("> " + command);
}


void Imap::readyRead() {
    Result result = BLANK;
    QString response;
    
    while (socket->canReadLine()) {
        response = socket->readLine();
        qDebug() << "< " << response;
        
        printLine("< " + response);
        
        if (response.startsWith("* BYE")) {
            disconnected();            
        }
        
        switch (currentCommand) {
            case LOGIN:
            {
                result = parseResponseCode(response);
                break;
            }
            case LIST:
            {
                if (response.startsWith('*')) {
                    parseDirectory(response);
                    break;
                }
                else {
                    result = parseResponseCode(response);
                    if (result == OK) {  
                        indicator--;
                        break;
                    }
                }
            }
            case SELECT:
            {
                if (response.startsWith("* ")) {
                    QRegularExpression regEx("\\[UIDNEXT [0-9]{1,}", QRegularExpression::CaseInsensitiveOption);
                    QRegularExpressionMatch match = regEx.match(response);
                    
                    if (match.hasMatch()) {
                        bool ok = false;
                        
                        currentDir->setOldUidNext(currentDir->getUidNext());
                        
                        QString uid = match.captured(0);
                        uid = uid.mid(9);
                        
                        currentDir->setUidNext(uid.toUInt(&ok));
                    }
                    
                    break;
                }
                else {
                    result = parseResponseCode(response);
                    break;
                }
            }
            case FETCH:
            {
                if (parseResponseCode(response) != BLANK) {
                    result = parseResponseCode(response);
                    break;
                }
                
                if (response.startsWith("* ")) {
                    mailDummy = new Mail();
                    currentDir->addMail(mailDummy);

                    QRegularExpression regEx("\\(UID [0-9]{1,} FLAGS \\(.*\\) ", QRegularExpression::CaseInsensitiveOption);
                    QRegularExpressionMatch match = regEx.match(response);
                    
                    if (match.hasMatch()) {                   
                        if (match.captured(0).toUpper().contains("\\SEEN")) {
                            mailDummy->readMail();
                        }
                        
                        regEx.setPattern("[0-9]{1,}");
                        match = regEx.match(match.captured(0));
                        
                        bool ok = false;
                        
                        if (match.hasMatch()) {
                            mailDummy->setUid(match.captured(0).toUInt(&ok));
                        }
                    }
                    
                    break;
                }
                else {
                    parseFetchResponse(response);
                    break;
                }
            }
            case STORE:
            {
                result = parseResponseCode(response);
                break;
            }
            case EXPUNGE:
            {
                result = parseResponseCode(response);
                break;
            }
            case NOOP:
            {
                result = parseResponseCode(response);
                break;
            }
        }
    }
    
    switch (currentCommand) {
        case LOGIN:
        {
            if (result == OK) {
                fetchDirectories();
            }
            else if (result == BAD) {
                currentCommand = DEFAULT;
                qDebug() << "ERROR: SYNTAX ERROR";
            }
            else if (result == NO) {
                currentCommand = DEFAULT;
                qDebug() << "ERROR: ACCESS PERMITTED";
            }
            
            break;
        }
        case LIST:
        {
            if (result == OK) {
                if (indicator == 0) {
                    emit directoriesFetched();
                    connected = true;
                    directoryListReady = true;
                }
            }
            
            break;
        }
        case SELECT:
        {
            if (result == OK) {
                fetchMail(currentDir);
            }
            
            break;
        }
        case FETCH:
        {
            if (result == OK) {
                textIncoming = false;
                
                emit fetchCompleted();
            }
            
            break;
        }
        case LOGOUT:
        {
            emit pipeReady();   
            break;
        }
    }
    
    if (result == OK || result == NO || result == BAD) {
        currentCommand = DEFAULT;
        emit pipeReady();
    }
}


Imap::Result Imap::parseResponseCode(QString response) {
    QRegularExpression regEx;
    QRegularExpressionMatch match;
    int counter = 0;
    
    foreach (QString pattern, responsePattern) {
        regEx.setPattern(pattern);
        match = regEx.match(response);
        
        if (match.hasMatch()) {
            return (Imap::Result)counter;
        }
        
        counter++;
    }
    
    return BLANK;
}


void Imap::parseFetchResponse(QString response) {
    if (response.startsWith("Date: ")) {
        QString tmpTimeStamp = response.mid(response.indexOf(" ")+ 1);
        tmpTimeStamp = tmpTimeStamp.mid(0, tmpTimeStamp.lastIndexOf(" "));
                        
        QLocale engLocale(QLocale("en_US"));
        QLocale::setDefault(engLocale);
                                               
        QDateTime dateTime = QLocale().toDateTime(tmpTimeStamp, "ddd, d MMM yyyy HH:mm:ss");
                        
        mailDummy->setTimeStamp(dateTime);
    }
    else if (response.startsWith("Subject: ")) {
        QString tmpSubject = response.mid(response.indexOf(" ") + 1);
        tmpSubject = tmpSubject.mid(0, tmpSubject.length() - 2);
                        
        mailDummy->setSubject(tmpSubject);
    }
    else if (response.startsWith("From: ")) {
        QString tmpSenderName = response.mid(response.indexOf(" ") + 1);
        tmpSenderName = tmpSenderName.mid(0, tmpSenderName.indexOf("<") - 1);
                        
        mailDummy->setSenderName(tmpSenderName);
                        
        QString tmpSenderAddress = response.mid(response.indexOf("<") + 1);
        tmpSenderAddress = tmpSenderAddress.mid(0, tmpSenderAddress.indexOf(">"));
                        
        mailDummy->setSenderAddress(tmpSenderAddress);
    }
    else if (response.startsWith(" BODY[TEXT]")) {
        textIncoming = true;
    }    
    else if (textIncoming == true) {
        if (response != ")\r\n")
            mailDummy->setText(mailDummy->getText().append(response));
    }
}


bool Imap::isConnected() {
    return this->connected;
}

void Imap::connect() {
    socket = new QSslSocket(this);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(connectionReady()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->connectToHostEncrypted(host, port);
}

void Imap::connectionReady() {
    stream = new QTextStream(socket);
    stream->setCodec("UTF-8");
    qDebug() << "Connected.";
    
    connected = true;
    
    emit connectedChanged();
    
    queue.connected();
    
    login();
}

void Imap::disconnected() {
    qDebug() << "Disconnected.";
    connected = false;
    directoryListReady = false;
    queue.disconnected();
    queue.clear();
    emit connectedChanged();
}


void Imap::login() {
    queue.push("LOGIN " + userLogin + " " + userPassword);
}

/*
 * Logout
 */

void Imap::logout() {
    queue.push("LOGOUT");
}


void Imap::fetchDirectories(QString root) {
    indicator++;

    queue.push("LIST \"\" " + ((root == "")?("%"):(root + "/%")));
}

void Imap::parseDirectory(QString response) {
    QRegularExpression regEx("\"[^/ ]((.*)+)\"", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regEx.match(response);              
                
    if (match.hasMatch()) {
        QString dirName = match.captured(0).mid(1, match.captured(0).length() - 2);
            
        if (response.contains("\\HasChildren")) {
            fetchDirectories(dirName);
        }
            
        addToHierarchy(dirName);
    }
}

void Imap::addToHierarchy(QString path, Directory* parent) {
    if (path.contains("/")) {
        QString parentDirectory = path.mid(0, path.indexOf("/"));
        foreach(Directory* dir, directoryList) {
            if (dir->getName() == parentDirectory) {
                addToHierarchy(path.mid(path.indexOf("/") + 1), dir);               
                
                break;
            }
        }
    }
    else {
        Directory *tmpDir = new Directory(stringFromImap(path));        
        
        if (parent == 0) {
            tmpDir->setParentDirectory(0);
            
            tmpDir->setParentId(-1);
            tmpDir->setId(nextDirectoryId());
        }
        else {
            tmpDir->setParentDirectory(parent);
            
            tmpDir->setParentId(parent->getId());
            tmpDir->setId(nextDirectoryId());
        }
        
        
        if (getDirectoryByPath(buildPath(tmpDir), repository->getDirectoriesHierarchically()) != 0) {
            delete tmpDir;
            tmpDir = getDirectoryByPath(buildPath(tmpDir), repository->getDirectoriesHierarchically());
        }
        else {
            if (parent != 0) {
                parent->addSubDirectory(tmpDir);
            }
        }
        
        
        if (parent == 0) {
            flatDirectoryList.append(tmpDir);   
            directoryList.append(tmpDir);
        }
        else {
            flatDirectoryList.append(tmpDir);
        }
    }
}


void Imap::selectDirectory(Directory* dir) {
    queue.push("SELECT " + buildPath(dir), dir);
}


void Imap::fetchMail(Directory* dir, unsigned int uid) {    
    if (uid != 0) {
        queue.push("UID FETCH " + QString::number(uid) + " (FLAGS BODY.PEEK[HEADER.FIELDS (FROM SUBJECT DATE)] BODY.PEEK[TEXT])", dir);
    }
    else {
       queue.push("FETCH 1:* (FLAGS UID BODY.PEEK[HEADER.FIELDS (FROM SUBJECT DATE)] BODY.PEEK[TEXT])", dir); 
    }
}

void Imap::deleteMail(Mail* mail, Directory* dir) {    
    queue.push("UID STORE " + QString::number(mail->getUid()) + " +FLAGS \\Deleted");
    
    dir->removeMail(mail);
    
    queue.push("EXPUNGE");
}

void Imap::readMail(Mail* mail, Directory* dir) {    
    queue.push("UID STORE " + QString::number(mail->getUid()) + " +FLAGS \\Seen");
}

void Imap::unreadMail(Mail* mail, Directory* dir) {
    queue.push("UID STORE " + QString::number(mail->getUid()) + " -FLAGS \\Seen");
}


void Imap::listDirectories() {
    foreach (Directory* dir, directoryList) {
        qDebug() << "--" << dir->getName();
        foreach (Directory* dir2, dir->getSubDirectories()) {
            qDebug() << "----" << dir2->getName();
        }
    }
}


QList<Directory*> Imap::getDirectories() {
    return directoryList;
}

int Imap::nextDirectoryId() {
    int nextId = 0;
    
    do {
        nextId = directoryId++;
    }
    while (idExists(nextId));
    
    return nextId;
}

QList<Directory*> Imap::getFlatDirectoryList() {
    return this->flatDirectoryList;
}

bool Imap::idExists(int id) {
    foreach (Directory* dir, repository->getAllDirectories()) {
        if (dir->getId() == id) {
            return true;
        }
    }
    
    return false;
}

void Imap::setTimeout(unsigned int timeout) {
    queue.setInterval(timeout * 1000);
}

void Imap::setCredentials(Settings* s) {
    if (this->isConnected()) {
        logout();
    }
    
    queue.clear();
    
    this->userLogin = s->getImapLogin();
    this->userPassword = s->getImapPassword();
    this->host = s->getImapHost();
    this->port = s->getImapPort();
    
    setTimeout(s->getImapTimeout());
    
    connect();
}

bool Imap::isDirectoryListReady() {
    return directoryListReady;
}

void Imap::clearDirectories() {
    directoryList.clear();
    flatDirectoryList.clear();
}