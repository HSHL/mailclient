/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imap.h
 * Author: ckarner
 *
 * Created on November 23, 2015, 12:25 PM
 */

#ifndef IMAP_H
#define IMAP_H

#include <QtNetwork>
#include <QObject>
#include <QList>
#include "Queue.h"
#include "Directory.h"
#include "Settings.h"

class DataRepository;

class Imap : public QObject {
    Q_OBJECT
public:
    Imap(DataRepository *repository);
    ~Imap();
    Imap(const Imap& imap);
    
    QList<Directory*> getDirectories();
    
    void selectDirectory(Directory *dir);
    void fetchMail(Directory* dir, unsigned int uid = 0);
    
    bool isConnected();
    
    void login();
    void logout();
    
    void setTimeout(unsigned int timeout);
    
    void readMail(Mail* mail, Directory* dir);
    void unreadMail(Mail* mail, Directory* dir);
    
    void deleteMail(Mail* mail, Directory* dir);
    
    QList<Directory*> getFlatDirectoryList();
    
    void setCredentials(Settings *s);
    
    bool isDirectoryListReady();
    
    void clearDirectories();
    
private:
    enum Result { OK, NO, BAD, BLANK };
    enum Command { LOGIN, LIST, SELECT, FETCH, STORE, EXPUNGE, DEFAULT, NOOP, LOGOUT };
    Command currentCommand;
    Directory* currentDir;
    bool textIncoming;
    
    static unsigned short int tagPrefix;
    static unsigned short int tagNumber;
    
    QList<QString> responsePattern;
    unsigned int indicator;
    bool connected;
    
    void setCurrentCommand(QString cmd);
    
    DataRepository *repository;
    
    Mail* mailDummy;
    
    Queue queue;
    
    QString userLogin;
    QString userPassword;
    QString host;
    unsigned short int port;
    
    QList<Directory*> directoryList;
    
    QSslSocket* socket;
    QTextStream* stream;
    
    QString nextTag();
    void connect();
    void initialize();
    
    QString stringFromImap(QString input);
    QString stringToImap(QString input);
    
    Result parseResponseCode(QString response);
    
    QString buildPath(Directory* dir);
    Directory* getDirectoryByPath(QString path, QList<Directory*> list);
    
    void fetchDirectories(QString root = "");
    void parseDirectory(QString response);
    void addToHierarchy(QString path, Directory* parent = 0);
    
    
    void parseFetchResponse(QString response);
    
    void listDirectories();
    
    QList<Directory*> flatDirectoryList;
    int directoryId;
    int nextDirectoryId();
    
    bool idExists(int id);
    
    bool directoryListReady;
    
private slots:
    void connectionReady();
    void readyRead();
    void disconnected();
    void sendCommand(QString cmd, Directory* dir);

signals:
    void directoriesFetched();
    void pipeReady();
    void fetchCompleted();
    void connectedChanged();
    void printLine(QString s);
};

#endif /* IMAP_H */

