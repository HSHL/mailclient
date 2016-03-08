/* 
 * File:   Mail.cpp
 * Author: ckarner
 * 
 * Created on October 15, 2015, 11:35 AM
 */

#include "Mail.h"
#include <QString>

Mail::Mail() {
    this->read = false;
}

void Mail::setSenderAddress(QString value) {
    this->senderAddress = value;
    
    return;
}

QString Mail::getSenderAddress() const {
    return this->senderAddress;
}

void Mail::setRecipientAddress(QString value) {
    this->recipientAddress = value;
    
    return;
}

QString Mail::getRecipientAddress() const {
    return this->recipientAddress;
}

void Mail::setSubject(QString value) {
    this->subject = value;
    
    return;
}

QString Mail::getSubject() const {
    return this->subject;
}

void Mail::setText(QString value) {
    this->text = value;
    
    return;
}

QString Mail::getText() const {
    return this->text;
}

void Mail::setTimeStamp(QDateTime value) {
    this->timeStamp = value;
    
    return;
}

QDateTime Mail::getTimeStamp() const {
    return this->timeStamp;
}

void Mail::setUid(unsigned int uid) {
    this->uid = uid;
    
    return;
}

unsigned int Mail::getUid() const {
    return this->uid;
}

bool Mail::isRead() const {
    return read;
}

void Mail::readMail() {
    read = true;
    
    return;
}

void Mail::unreadMail() {
    read = false;
    
    return;
}

void Mail::setRead(bool value) {
    this->read = value;
    
    return;
}

void Mail::setSenderName(QString senderName) {
    this->senderName = senderName;
    
    return;
}

QString Mail::getSenderName() const {
    return this->senderName;
}