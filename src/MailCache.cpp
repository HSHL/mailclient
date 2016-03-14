/* 
 * File:   DataRepository.cpp
 * Author: ckarner
 * 
 * Created on October 19, 2015, 2:59 PM
 */

#include "MailCache.h"
#include "Contact.h"
#include <QDebug>
#include "Directory.h"
#include "Logger.h"
#include <QMutableListIterator>

MailCache::MailCache() {
    Logger::debug("MailCache.constructor");
    directoryId = -1;
}

int MailCache::nextDirectoryId() {
    directoryId++;
    return directoryId;
}

const QList<Directory*> MailCache::getAllDirectories() const {
    return directoryList;
}

void MailCache::addDirectory(Directory* dir) {
    if (dir == NULL)
        return;
    
    if (dir->getId() == -2) {
        dir->setId(nextDirectoryId());
    }
    
    if (!directoryList.contains(dir)) {
        directoryList.append(dir);
        emit directoryAdded(dir);
    }
}

void MailCache::removeDirectory(Directory *dir) {
    if (dir == NULL)
        return;

    directoryList.removeAll(dir);
    delete dir;
    emit directoriesChanged();
}

const QList<Directory*> MailCache::getSubDirectories(Directory* parentDir) const {
    QList<Directory*> result;
    foreach (Directory* dir, directoryList) {
        if (dir->getParentDirectory() == parentDir)
            result.append(dir);
    }
    
    return result;
}

Directory* MailCache::getDirectoryByPath(QString path) {
    foreach (Directory* dir, directoryList) {
        if (dir->getPath() == path)
            return dir;
    }
    
    return 0;
}

void MailCache::clearDirectories() {
    directoryList.clear();
    emit directoriesChanged();
}

void MailCache::addDirectory(QString path) {
    Logger::debug("MailCache.addDirectory: " + path);
    
    QStringList parts = path.split("/");
    if (parts.size() == 1) {
        Directory *dir = new Directory(parts[0]);
        addDirectory(dir);
    }
}

void MailCache::addMail(Mail* mail) {
    mailList.append(mail);
}

void MailCache::clearMails() {
    mailList.clear();
}

void MailCache::removeMail(Mail* mail) {
    mailList.removeAll(mail);
}

const QList<Mail*> MailCache::getMailsInDirectory(Directory* dir) const {
    QList<Mail*> result;
    foreach (Mail *m, mailList) {
        if (m->getDirectory() == dir)
            result.append(m);
    }
    
    return result;
}

void MailCache::removeMailsInDirectory(Directory* dir) {
    QMutableListIterator<Mail*> i(mailList);
    while (i.hasNext()) {
        Mail *m = i.next();
        if (m->getDirectory() == dir) {
            i.remove();
            delete m;
        }
    }
}