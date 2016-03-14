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

#include <QByteArray>
#include "Smtp.h"
#include "MailCache.h"
#include "Base64.h"
#include "Directory.h"
#include <QMessageBox>
#include "Mail.h"
#include "Logger.h"

Smtp::Smtp(QSettings *settings) {
    Logger::debug("Smtp.constructor");
    
    this->settings = settings;
    queue.setInterval(0);
    initialize();
}

void Smtp::initialize() {
    Logger::debug("Smtp.initialize");
    
    state = NONE;
    QObject::connect(this, SIGNAL(pipeReady()), &queue, SLOT(pipeReady()));
    QObject::connect(&queue, SIGNAL(nextCommand(QString, Directory*)), this, SLOT(sendCommand(QString)));
}

void Smtp::sendCommand(QString cmd) {
    Logger::debug("Smtp.sendCommand: " + cmd);

    QString command = cmd + "\r\n";
    *stream << command;
    stream->flush();
}

void Smtp::connect() {
    Logger::debug("Smtp.connect");
    
    socket = new QSslSocket(this);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(connectionReady()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->connectToHost(settings->value("SMTP/host").toString(), settings->value("SMTP/port").toInt());
}

void Smtp::disconnected() {
    Logger::debug("Smtp.disconnected");
    state = NONE;
}

void Smtp::connectionReady() {
    Logger::debug("Smtp.connectionReady");
    
    stream = new QTextStream(socket);
    stream->setCodec("UTF-8");
}

void Smtp::readyRead() {
    Logger::debug("Smtp.readyRead");
    
    QString response;
    while (socket->canReadLine()) {
        response = socket->readLine().simplified();
        Logger::debug("Smtp.readyRead: " + response);
    }
    
    if (state == NONE) {
        if (response.startsWith("220")) {
            state = CONNECTED;
            queue.push("HELO there");
        }        
    }
    else if (state == CONNECTED && settings->value("SMTP/tls").toBool()) {
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
        queue.push(Base64::toBase64(settings->value("SMTP/login").toString()));
    }
    else if (state == LOGIN_PASSWORD) {
        state = MAILFROM;
        queue.push(Base64::toBase64(settings->value("SMTP/password").toString()));
    }
    else if (state == MAILFROM) {
        if (response.startsWith("235")) {
            state = RCPTTO;
            queue.push("MAIL FROM:<" + settings->value("SMTP/login").toString() +">");
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
            queue.push("FROM:<" + settings->value("SMTP/login").toString() + ">\r\nTO:<" + recipient + ">\r\nSUBJECT:" + subject + "\r\n\r\n" + text + "\r\n.");
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

void Smtp::sendMail(Mail *mail) {
    Logger::debug("Smtp.sendMail");
    
    if (settings->value("SMTP/host").toString() != "" && 
        settings->value("SMTP/port").toInt() != 0 && 
        settings->value("SMTP/login").toString() != "" && 
        settings->value("SMTP/password").toString() != "") {
        this->recipient = mail->getRecipientAddress();
        this->subject = mail->getSubject();
        this->text = mail->getText();
        connect();
    }
    else {
        QMessageBox(QMessageBox::Information, "Error", "Please enter your SMTP-credentials.").exec();
    }
}