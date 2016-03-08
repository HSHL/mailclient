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
#include "Contact.h"
#include "Directory.h"
#include "Settings.h"
#include "Interface.h"

class DataRepository: public QObject {
    Q_OBJECT
public:
    DataRepository();
    int nextContactId();
    int nextDirectoryId();
    const QList<Contact*> getAllContacts() const;
    const QList<Directory*> getAllDirectories() const;
    const QList<Directory*> getDirectoriesHierarchically() const;
    void save(Contact *c);
    void save(Directory *c);
    void remove(Directory *c);
    void remove(Contact *c);
    void addToHierarchy(Directory *dir);
    void clearDirectories();
    
    Interface* getInterface() const;
    
    Settings* getSettings() const;
private:
    int contactId;
    int directoryId;
    QList<Contact*> contactList;
    QList<Directory*> directoryList;
    QList<Directory*> hierarchicalDirectoryList;
    
    Settings* settings;
    Interface* interface;
    
signals:
    void contactsChanged();
    //void directoriesChanged();
    void refreshDirectories();
public slots:
    void getDirectoriesFromImap();
    void updateSettings();
};

#endif	/* DATAREPOSITORY_H */

