/* 
 * File:   DataRepository.cpp
 * Author: ckarner
 * 
 * Created on October 19, 2015, 2:59 PM
 */

#include "DataRepository.h"
#include "Contact.h"
#include <QDebug>
#include "Directory.h"

DataRepository::DataRepository() {
    contactId = -1;
    directoryId = -1;
}

int DataRepository::nextContactId() {
    contactId++;
    return contactId;
}

int DataRepository::nextDirectoryId() {
    directoryId++;
    return directoryId;
}

const QList<Contact*> DataRepository::getAllContacts() const {
    return contactList;
}


const QList<Directory*> DataRepository::getAllDirectories() const {
    return directoryList;
}

const QList<Directory*> DataRepository::getDirectoriesHierarchically() const {
    return hierarchicalDirectoryList;
}

void DataRepository::save(Contact* c) {
    if (c == NULL)
        return;
    
    if (c->id() == -1)
        c->setId(nextContactId());
    else
        nextContactId();
            
    if (!contactList.contains(c)) {
        contactList.append(c);
    }
    
    emit contactsChanged();
    
    return;
}

void DataRepository::save(Directory* dir) {
    if (dir == NULL)
        return;
    
    if (dir->getId() == -2) {
        dir->setId(nextDirectoryId());
    }
    else {
        nextDirectoryId();    
    }
    
    if (!directoryList.contains(dir)) {
        directoryList.append(dir);
    }
    
    return;
}

void DataRepository::remove(Contact *c) {
    if (c == NULL) {
        return;
    }
    
    contactList.removeAll(c);
    
    delete c;
    
    emit contactsChanged();
    
    return;
}

void DataRepository::remove(Directory *dir) {
    if (dir == NULL) {
        return;
    }
    
    directoryList.removeAll(dir);
    
    delete dir;
    
    return;
}

void DataRepository::addToHierarchy(Directory* dir) {
    this->hierarchicalDirectoryList.append(dir);
    
    return;
}
