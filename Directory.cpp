/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Directory.cpp
 * Author: ckarner
 * 
 * Created on November 30, 2015, 9:19 AM
 */

#include "Directory.h"
#include <QString>
#include "Mail.h"

Directory::Directory() {
    this->id = -2;
    this->name = name;
    this->parent = parent;
    
    this->uidNext = 0;
    this->oldUidNext = 0;
    this->uidValidity = 0;
}

Directory::Directory(QString name, Directory* parent) {
    this->id = -2;
    this->name = name;
    this->parent = parent;
    
    this->uidNext = 0;
    this->uidValidity = 0;
}

void Directory::setName(QString name) {
    this->name = name;
}

QString Directory::getName() const {
    return this->name;
}

void Directory::setId(int id) {
    this->id = id;
    
    return;
}

int Directory::getId() const {
    return this->id;
}

void Directory::setParentId(int parentId) {
    this->parentId = parentId;
}

int Directory::getParentId() const {
    return this->parentId;
}

void Directory::setParentDirectory(Directory* parent) {
    this->parent = parent;
    
    return;
}

Directory* Directory::getParentDirectory() const {
    return this->parent;
}

QList<Directory*> Directory::getSubDirectories() const {
    return this->directoryList;
}

void Directory::addSubDirectory(Directory* dir) {
    this->directoryList.append(dir);
    
    return;
}

void Directory::removeSubDirectory(Directory* dir) {
    this->directoryList.removeAll(dir);
    
    return;
}

void Directory::setUidNext(unsigned int uidNext) {
    this->uidNext = uidNext;
    
    return;
}

unsigned int Directory::getUidNext() const {
    return this->uidNext;
}

void Directory::setOldUidNext(unsigned int oldUidNext) {
    this->oldUidNext = oldUidNext;
    
    return;
}

unsigned int Directory::getOldUidNext() const {
    return this->oldUidNext;
}

void Directory::setUidValidity(unsigned int uidValidity) {
    this->uidValidity = uidValidity;
    
    return;
}

unsigned int Directory::getUidValidity() const {
    return this->uidValidity;
}

bool Directory::hasChildren() const {
    return (this->directoryList.count() != 0)?(true):(false);
}

void Directory::addMail(Mail* mail) {
    this->mailList.append(mail);
    
    return;
}

QList<Mail*> Directory::getMailList() const {
    return this->mailList;
}

void Directory::setMailList(const QList<Mail*> mailList) {
    this->mailList = mailList;
}

Directory::~Directory() {
    foreach(Directory* dir, directoryList) {
        delete dir;
        
        foreach (Mail* mail, mailList) {
            delete mail;
        }
        
        mailList.clear();
    }
}

void Directory::clearMail() {
    this->mailList.clear();
}

void Directory::removeMail(Mail* mail) {
    this->mailList.removeAll(mail);
    
    return;
}