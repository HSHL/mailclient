/* 
 * File:   DataRepository.h
 * Author: ckarner
 *
 * Created on October 19, 2015, 2:59 PM
 */

#ifndef DATAREPOSITORY_H
#define	DATAREPOSITORY_H

#include <QObject>
#include <QList>
#include <QString>
#include "Directory.h"
#include "Mail.h"

class MailCache: public QObject {
    Q_OBJECT
    
public:
    MailCache();
    int nextDirectoryId();
    const QList<Directory*> getAllDirectories() const;
    const QList<Directory*> getSubDirectories(Directory* dir) const;
    Directory* getDirectoryByPath(QString path);
    void addDirectory(Directory *c);
    void addDirectory(QString path);
    void removeDirectory(Directory *c);
    void clearDirectories();
    void addMail(Mail *mail);
    void removeMail(Mail *mail);
    void clearMails();
    const QList<Mail*> getMailsInDirectory(Directory *dir) const;
    void removeMailsInDirectory(Directory* dir);
    
private:
    int directoryId;
    QList<Directory*> directoryList;
    QList<Mail*> mailList;
    
signals:
    void directoriesChanged();
    void directoryAdded(Directory *directory);
};

#endif	/* DATAREPOSITORY_H */