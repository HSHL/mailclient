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
}

QString Mail::getSenderAddress() const {
    return this->senderAddress;
}

void Mail::setRecipientAddress(QString value) {
    this->recipientAddress = value;
}

QString Mail::getRecipientAddress() const {
    return this->recipientAddress;
}

void Mail::setSubject(QString value) {
    this->subject = value;
}

QString Mail::getSubject() const {
    return this->subject;
}

void Mail::setText(QString value) {
    this->text = value;
}

QString Mail::getText() const {
    return this->text;
}

void Mail::setTimeStamp(QDateTime value) {
    this->timeStamp = value;
}

QDateTime Mail::getTimeStamp() const {
    return this->timeStamp;
}

void Mail::setUid(unsigned int uid) {
    this->uid = uid;
}

unsigned int Mail::getUid() const {
    return this->uid;
}

bool Mail::isRead() const {
    return read;
}

void Mail::readMail() {
    read = true;
}

void Mail::unreadMail() {
    read = false;
}

void Mail::setRead(bool value) {
    this->read = value;
}

void Mail::setSenderName(QString senderName) {
    this->senderName = senderName;
}

QString Mail::getSenderName() const {
    return this->senderName;
}