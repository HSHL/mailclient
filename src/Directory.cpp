/* 
 * File:   Directory.cpp
 * Author: ckarner
 * 
 * Created on November 30, 2015, 9:19 AM
 */

#include "Directory.h"
#include <QString>
#include "Mail.h"

Directory::Directory(QString name, Directory* parent) {
    this->id = -2;
    this->name = name;
    this->parent = parent;
    
    this->uidNext = 0;
    this->oldUidNext = 0;
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
}

int Directory::getId() const {
    return this->id;
}

void Directory::setParentDirectory(Directory* parent) {
    this->parent = parent;
}

Directory* Directory::getParentDirectory() const {
    return this->parent;
}

void Directory::setUidNext(unsigned int uidNext) {
    this->uidNext = uidNext;
}

unsigned int Directory::getUidNext() const {
    return this->uidNext;
}

void Directory::setOldUidNext(unsigned int oldUidNext) {
    this->oldUidNext = oldUidNext;
}

unsigned int Directory::getOldUidNext() const {
    return this->oldUidNext;
}

void Directory::setUidValidity(unsigned int uidValidity) {
    this->uidValidity = uidValidity;
}

unsigned int Directory::getUidValidity() const {
    return this->uidValidity;
}

QString Directory::getPath() {
    if (parent == NULL)
        return "/" + getName();
    else 
        return parent->getPath() + "/" + getName();
}
