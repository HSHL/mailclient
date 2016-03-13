/* 
 * File:   Contact.cpp
 * Author: ckarner
 * 
 * Created on October 15, 2015, 11:32 AM
 */

#include "Contact.h"
#include <QString>

Contact::Contact() {
    _id = -1;
    this->_firstName = "";
    this->_lastName = "";
    this->_mailAddress = "";
}

Contact::Contact(QString firstName, QString lastName, QString mailAddress) {
    _id = -1;
    this->_firstName = firstName;
    this->_lastName = lastName;
    this->_mailAddress = mailAddress;    
}

void Contact::setId(int id) {
    _id = id;
}

int Contact::id() const {
    return _id;
}

QString Contact::firstName() const {
    return _firstName;
}

void Contact::firstName(QString firstName) {
    this->_firstName = firstName;
}

QString Contact::lastName() const {
    return _lastName;
}

void Contact::lastName(QString lastName) {
    this->_lastName = lastName;
}

QString Contact::mailAddress() const {
    return _mailAddress;
}

void Contact::mailAddress(QString mailAddress) {
    this->_mailAddress = mailAddress;
}