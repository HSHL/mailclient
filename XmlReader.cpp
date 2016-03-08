/* 
 * File:   XmlReader.cpp
 * Author: ckarner
 * 
 * Created on October 23, 2015, 10:05 PM
 */

//#include <qt/QtCore/qxmlstream.h>

#include "XmlReader.h"
#include "DataRepository.h"
#include "Contact.h"
#include "AddressBook.h"
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include "Directory.h"
#include <QDebug>
#include "Settings.h"
#include "Mail.h"
#include "Base64.h"

XmlReader::XmlReader(DataRepository* repository) {
    this->repository = repository;
    
    connect(this, SIGNAL(completed()), repository, SLOT(updateSettings()));
}

void XmlReader::readContact() {
    Contact* c = new Contact();
    c->setId(reader.attributes().value("ID").toString().toInt());
    c->firstName(reader.attributes().value("firstName").toString());
    c->lastName(reader.attributes().value("lastName").toString());
    c->mailAddress(reader.attributes().value("mailAddress").toString());
    this->repository->save(c);
}

void XmlReader::readDirectory() {
    Directory* dir = new Directory();
    currentDir = dir;
    bool ok = false;
    dir->setId(reader.attributes().value("ID").toString().toInt());
    dir->setName(reader.attributes().value("name").toString());
    dir->setParentId(reader.attributes().value("parent").toString().toInt());
    dir->setUidNext((reader.attributes().value("uidNext").toString().toUInt(&ok)));
    this->repository->save(dir);
}

void XmlReader::readImap() {
    bool ok = false;
    Settings *s = repository->getSettings();
    s->setImapLogin(reader.attributes().value("login").toString());
    s->setImapPassword(reader.attributes().value("password").toString());
    s->setImapHost(reader.attributes().value("host").toString());
    s->setImapPort(reader.attributes().value("port").toString().toUInt(&ok));
    s->setImapTimeout(reader.attributes().value("timeout").toString().toUInt(&ok));
}

void XmlReader::readSmtp() {
    bool ok = false;
    Settings* s = repository->getSettings();
    s->setSmtpLogin(reader.attributes().value("login").toString());
    s->setSmtpPassword(reader.attributes().value("password").toString());
    s->setSmtpHost(reader.attributes().value("host").toString());
    s->setSmtpPort(reader.attributes().value("port").toString().toUInt(&ok));
    s->setTls(reader.attributes().value("tls").toString().toInt(&ok));
}

void XmlReader::readMail() {
    bool ok = false;
    Mail* m = new Mail();
    currentDir->addMail(m);
    m->setRecipientAddress(reader.attributes().value("recipientAddress").toString());
    m->setSenderName(reader.attributes().value("senderName").toString());
    m->setSenderAddress(reader.attributes().value("senderAddress").toString());
    m->setSubject(reader.attributes().value("subject").toString());
    m->setText(Base64::fromBase64(reader.attributes().value("text").toString()));
    m->setTimeStamp(QDateTime::fromString(reader.attributes().value("timestamp").toString()));
    m->setUid(reader.attributes().value("uid").toString().toUInt(&ok));
    m->setRead(reader.attributes().value("isRead").toString().toInt(&ok));
}

Directory* XmlReader::getParentDirectoryById(int parentId) {
    if (parentId == -1) {
        return 0;
    }
    
    foreach (Directory* dir, this->repository->getAllDirectories()) {
        if (dir->getId() == parentId) {
            return dir;
        }
    }
    
    //Not to be reached:
    return 0;
}

void XmlReader::parse() {
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "Contact")
               readContact();
        
            if (reader.name() == "Directory")
                readDirectory();
            if (reader.name() == "Imap")
                readImap();
            if (reader.name() == "Smtp")
                readSmtp();
            if (reader.name() == "Mail")
                readMail();
        }
        
        reader.readNext();
    }
}

bool XmlReader::read() {
    QFile file(QDir::currentPath() + "/data.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::warning(NULL, "Information", "Could not load data.");
        return false;
    }
    
    this->reader.setDevice(&file);
    parse();
    file.close();
    
    associateDirectories();
    
    buildHierarchicalList();
    
    associateMails();
    
    emit completed();
    
    return true;
}

void XmlReader::associateDirectories() {
    Directory *parent;
    foreach(Directory* dir, this->repository->getAllDirectories()) {
        parent = getParentDirectoryById(dir->getParentId());
        if (parent != 0) {
            dir->setParentDirectory(parent);
            parent->addSubDirectory(dir);
        }
        else {
            dir->setParentDirectory(0);
        }
    }
}

void XmlReader::associateMails() {
    
}

void XmlReader::buildHierarchicalList() {
    foreach (Directory *dir, this->repository->getAllDirectories()) {
        if (dir->getParentId() == -1) {
            this->repository->addToHierarchy(dir);
        }
    }
}