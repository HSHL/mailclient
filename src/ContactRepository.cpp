/* 
 * File:   ContactRepository.cpp
 * Author: Alexander Stuckenholz
 * 
 * Created on 14. März 2016, 08:36
 */

#include "ContactRepository.h"
#include <QFile>
#include <QDir>
#include <QDomElement>
#include <QDomDocument>
#include <QMessageBox>
#include <QTextStream>
#include <QXmlStreamReader>
#include "Logger.h"

ContactRepository::ContactRepository(QString filename) {
    Logger::debug("ContactRepository.constructor: " + filename);
    this->filename = filename;
    this->contactId = -1;
    readFromFile();
}

int ContactRepository::nextContactId() {
    contactId++;
    return contactId;
}

const QList<Contact*> ContactRepository::getAllContacts() const {
    return contactList;
}

void ContactRepository::save(Contact* c) {
    Logger::debug("ContactRepository.save");

    if (c == NULL)
        return;

    if (c->id() == -1)
        c->setId(nextContactId());
    else
        nextContactId();

    if (!contactList.contains(c)) {
        contactList.append(c);
    }

    writeToFile();
    emit contactsChanged();
}

void ContactRepository::remove(Contact *c) {
    Logger::debug("ContactRepository.remove");
    if (c == NULL)
        return;

    contactList.removeAll(c);
    delete c;
    writeToFile();
    emit contactsChanged();
}

bool ContactRepository::writeToFile() {
    Logger::debug("ContactRepository.writeToFile");

    QFile file(QDir::currentPath() + "/" + this->filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(NULL, "Information", "Couldn't save data.");
        return false;
    }

    QTextStream stream(&file);
    stream << getDocument();
    file.close();

    return true;
}

QString ContactRepository::getDocument() {
    Logger::debug("ContactRepository.getDocument");

    QDomDocument document;
    QDomElement root = document.createElement("MailClient");
    document.appendChild(root);

    QDomElement contactRoot = document.createElement("Contacts");
    root.appendChild(contactRoot);

    QList<Contact*> contactList = getAllContacts();

    for (int i = 0; i < contactList.count(); i++) {
        QDomElement contactElement = document.createElement("Contact");
        contactElement.setAttribute("ID", QString::number(i));
        contactElement.setAttribute("firstName", contactList.at(i)->firstName());
        contactElement.setAttribute("lastName", contactList.at(i)->lastName());
        contactElement.setAttribute("mailAddress", contactList.at(i)->mailAddress());
        contactRoot.appendChild(contactElement);
    }

    return document.toString();
}

bool ContactRepository::readFromFile() {
    Logger::debug("ContactRepository.readFromFile");
    contactList.clear();
    
    QFile file(QDir::currentPath() + "/" + this->filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::debug("ContactRepository.readFromFile: Could not open file!");
        return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);

    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "Contact") {
                Contact* c = new Contact();
                c->setId(reader.attributes().value("ID").toString().toInt());
                c->firstName(reader.attributes().value("firstName").toString());
                c->lastName(reader.attributes().value("lastName").toString());
                c->mailAddress(reader.attributes().value("mailAddress").toString());
                save(c);
            }
        }

        reader.readNext();
    }

    file.close();
    emit contactsChanged();
    return true;
}