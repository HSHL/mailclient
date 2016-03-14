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
#include <QSettings>
#include <QList>
#include "Queue.h"
#include "Directory.h"

class MailCache;

class Imap : public QObject {
    Q_OBJECT
    
public:
    Imap(MailCache *mailCache, QSettings *settings);
    ~Imap();
    void selectDirectory(Directory *dir);
    void fetchMail(Directory* dir, unsigned int uid = 0);
    bool isConnected();
    void login();
    void logout();
    void setTimeout(unsigned int timeout);
    void readMail(Mail* mail, Directory* dir);
    void unreadMail(Mail* mail, Directory* dir);
    void deleteMail(Mail* mail, Directory* dir);
    void connect();
    
private:
    enum Result { OK, NO, BAD, BLANK };
    enum Command { LOGIN, LIST, SELECT, FETCH, STORE, EXPUNGE, DEFAULT, NOOP, LOGOUT };
    
    MailCache *mailCache;
    QSettings *settings;
    Command currentCommand;
    Directory* currentDir;
    bool textIncoming;
    static unsigned short int tagPrefix;
    static unsigned short int tagNumber;
    QList<QString> responsePattern;
    unsigned int indicator;
    bool connected;
    void setCurrentCommand(QString cmd);
    Mail* mailDummy;
    Queue queue;
    QSslSocket* socket;
    QTextStream* stream;
    QString nextTag();
    void initialize();
    QString stringFromImap(QString input);
    QString stringToImap(QString input);
    Result parseResponseCode(QString response);
    void fetchDirectories(QString root = "");
    void parseDirectory(QString response);
    void parseFetchResponse(QString response);
    
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
};

#endif /* IMAP_H */