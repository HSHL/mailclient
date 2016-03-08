/* 
 * File:   Contact.h
 * Author: ckarner
 *
 * Created on October 15, 2015, 11:32 AM
 */

#ifndef PERSON_H
#define	PERSON_H

#include <QString>

class Contact {
public:
    Contact();
    Contact(QString firstName, QString lastName, QString mailAddress);
    
    void setId(int id);
    int id() const;
    
    QString firstName() const;
    void firstName(QString firstName);
    
    QString lastName() const;
    void lastName(QString lastName);
    
    QString mailAddress() const;
    void mailAddress(QString mailAddress);
    
private:
    int _id = 0;
    QString _firstName;
    QString _lastName;
    QString _mailAddress;
};

#endif	/* PERSON_H */

