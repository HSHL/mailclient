/* 
 * File:   ContactRepository.h
 * Author: Alexander Stuckenhol
 *
 * Created on 14. März 2016, 08:36
 */

#ifndef CONTACTREPOSITORY_H
#define	CONTACTREPOSITORY_H

#include <QObject>
#include <QList>
#include "Contact.h"

class ContactRepository : public QObject {
    Q_OBJECT
    
public:
    ContactRepository(QString filename);
    int nextContactId();
    const QList<Contact*> getAllContacts() const;
    void save(Contact *c);
    void remove(Contact *c);
    bool writeToFile();
    bool readFromFile();

private:
    QString filename;
    int contactId;
    QList<Contact*> contactList;
    QString getDocument();
    
signals:
    void contactsChanged();
};

#endif	/* CONTACTREPOSITORY_H */