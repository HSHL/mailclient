/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Smtp.cpp
 * Author: ckarner
 * 
 * Created on December 3, 2015, 12:04 PM
 */

#include <QDebug>
#include <QByteArray>
#include "Smtp.h"
#include "DataRepository.h"
#include "Base64.h"
#include "Directory.h"
#include <QMessageBox>

Smtp::Smtp(DataRepository* repository) {
    this->repository = repository;
    
    queue.setInterval(0);
    
    initialize();
}

void Smtp::initialize() {
    state = NONE;    
    
    QObject::connect(this, SIGNAL(pipeReady()), &queue, SLOT(pipeReady()));
    QObject::connect(&queue, SIGNAL(nextCommand(QString, Directory*)), this, SLOT(sendCommand(QString)));
}

void Smtp::sendCommand(QString cmd) {
    QString command = cmd + "\r\n";
    qDebug() << command;
    *stream << command;
    stream->flush();
    emit printLine(command);
}

void Smtp::connect() {
    socket = new QSslSocket(this);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(connectionReady()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << repository->getSettings()->getSmtpHost() << repository->getSettings()->getSmtpPort();
    socket->connectToHost(repository->getSettings()->getSmtpHost(), repository->getSettings()->getSmtpPort());
}

void Smtp::disconnected() {
    state = NONE;
    qDebug() << "Disconnected.";
}


void Smtp::connectionReady() {
    stream = new QTextStream(socket);
    stream->setCodec("UTF-8");
    
    qDebug() << "Connected.";
}

void Smtp::readyRead() {
    QString response;
    
    emit printLine(response);
    
    while (socket->canReadLine()) {
        response = socket->readLine();
        qDebug() << response;
    }
    
    if (state == NONE) {
        if (response.startsWith("220")) {
            state = CONNECTED;
            queue.push("HELO there");
        }        
    }
    else if (state == CONNECTED && repository->getSettings()->useTls()) {
        if (response.startsWith("250")) {
            state = PRETLS;
            queue.push("STARTTLS");
        }
    }
    else if (state == PRETLS) {
        if (response.startsWith("220")) {
            socket->startClientEncryption();
            state = LOGIN_USERNAME;
            queue.push("AUTH LOGIN");
        }
    }
    else if (state == LOGIN_USERNAME) {
        state = LOGIN_PASSWORD;
        queue.push(Base64::toBase64(repository->getSettings()->getSmtpLogin()));
    }
    else if (state == LOGIN_PASSWORD) {
        state = MAILFROM;
        queue.push(Base64::toBase64(repository->getSettings()->getSmtpPassword()));
    }
    else if (state == MAILFROM) {
        if (response.startsWith("235")) {
            state = RCPTTO;
            queue.push("MAIL FROM:<" + repository->getSettings()->getSmtpLogin() +">");
        }
    }
    else if (state == RCPTTO) {
        if (response.startsWith("250")) {
            state = DATA;
            queue.push("RCPT TO:<" + recipient + ">");
        }
    }
    else if (state == DATA) {
        if (response.startsWith("250")) {
            state = MAILINPUT;
            queue.push("DATA");
        }
        else {
            state = NONE;
            emit failure(response);
            queue.push("QUIT");
        }
    }
    else if (state == MAILINPUT) {
        if (response.startsWith("354")) {
            state = QUIT;
            queue.push("FROM:<" + this->repository->getSettings()->getSmtpLogin() + ">\r\nTO:<" + recipient + ">\r\nSUBJECT:" + subject + "\r\n\r\n" + text + "\r\n.");
        }
    }
    else if (state == QUIT) {
        if (response.startsWith("250")) {
            state = NONE;
            queue.push("QUIT");
            emit success(response);
        }
        else {
            state = NONE;
            queue.push("QUIT");
            emit failure(response);
        }
    }
    
    emit pipeReady();
}

void Smtp::sendMail(QString recipient, QString subject, QString text) {
    if (repository->getSettings()->getSmtpHost() != "" && QString::number(repository->getSettings()->getSmtpPort()) != "" && repository->getSettings()->getSmtpLogin() != "" && repository->getSettings()->getSmtpPassword() != "") {
        this->recipient = recipient;
        this->subject = subject;
        this->text = text;
    
        connect();
    }
    else {
        QMessageBox(QMessageBox::Information, "Error", "Please enter your SMTP-credentials.").exec();
    }
}