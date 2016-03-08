/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Smtp.h
 * Author: ckarner
 *
 * Created on December 3, 2015, 12:04 PM
 */

#ifndef SMTP_H
#define SMTP_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include "Queue.h"
#include <QSslSocket>
#include <QTextStream>

class DataRepository;

class Smtp : public QObject {
    Q_OBJECT
public:
    Smtp(DataRepository* repository);
    void sendMail(QString recipient, QString subject, QString text);
private:
    enum State { NONE, CONNECTED, PRETLS, LOGIN_USERNAME, LOGIN_PASSWORD, MAILFROM, RCPTTO, DATA, MAILINPUT, QUIT};
    
    State state;
    
    Queue queue;
    
    DataRepository* repository;
    
    QSslSocket *socket;
    QTextStream *stream;
    
    void initialize();
    void connect();
    
    QString recipient;
    QString subject;
    QString text;
    
signals:
    void pipeReady();
    void failure(QString response);
    void success(QString response);
    void printLine(QString s);

private slots:
    void connectionReady();
    void readyRead();
    void disconnected();
    void sendCommand(QString cmd);
};

#endif /* SMTP_H */

