/* 
 * File:   XmlWriter.cpp
 * Author: ckarner
 * 
 * Created on October 24, 2015, 2:49 PM
 */

#include "XmlWriter.h"
#include "AddressBook.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QList>
#include "Contact.h"
#include <QTextStream>
#include "DataRepository.h"
#include "Mail.h"
#include "Base64.h"

XmlWriter::XmlWriter(DataRepository* repository) {
    this->repository = repository;
}

bool XmlWriter::write() {
    QFile file(QDir::currentPath() + "/data.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(NULL, "Information", "Couldn't save data.");
        return false;
    }
    
    QTextStream stream(&file);
    stream << getDocument();
    file.close();
    
    return true;
}

QString XmlWriter::getDocument() {
    QDomDocument document;
    QDomElement root = document.createElement("MailClient");
    document.appendChild(root);
    
    QDomElement contactRoot = document.createElement("Contacts");
    root.appendChild(contactRoot);
    
    QList<Contact*> contactList = repository->getAllContacts();
    
    for (int i = 0; i < contactList.count(); i++) {
        QDomElement contactElement = document.createElement("Contact");
        contactElement.setAttribute("ID", QString::number(i));
        contactElement.setAttribute("firstName", contactList.at(i)->firstName());
        contactElement.setAttribute("lastName", contactList.at(i)->lastName());
        contactElement.setAttribute("mailAddress", contactList.at(i)->mailAddress());
        contactRoot.appendChild(contactElement);
    }
    
    QDomElement settingsRoot = document.createElement(("Settings"));
    root.appendChild(settingsRoot);
    
    QDomElement imap = document.createElement("Imap");
    imap.setAttribute("login", repository->getSettings()->getImapLogin());
    imap.setAttribute("password", repository->getSettings()->getImapPassword());
    imap.setAttribute("host", repository->getSettings()->getImapHost());
    imap.setAttribute("port", repository->getSettings()->getImapPort());
    imap.setAttribute("timeout", repository->getSettings()->getImapTimeout());
    
    settingsRoot.appendChild(imap);
    
    QDomElement smtp = document.createElement("Smtp");
    smtp.setAttribute("login", repository->getSettings()->getSmtpLogin());
    smtp.setAttribute("password", repository->getSettings()->getSmtpPassword());
    smtp.setAttribute("host", repository->getSettings()->getSmtpHost());
    smtp.setAttribute("port", repository->getSettings()->getSmtpPort());
    smtp.setAttribute("tls", repository->getSettings()->useTls());
    
    settingsRoot.appendChild(smtp);
    
    QDomElement directoryRoot = document.createElement("Directories");
    root.appendChild(directoryRoot);
    
    foreach (Directory* dir, repository->getAllDirectories()) {
        QDomElement directoryElement = document.createElement("Directory");
        directoryElement.setAttribute("ID", QString::number(dir->getId()));
        directoryElement.setAttribute("name", dir->getName());
        directoryElement.setAttribute("parent", QString::number(dir->getParentId()));
        directoryElement.setAttribute("uidNext", QString::number(dir->getUidNext()));
        directoryRoot.appendChild(directoryElement);
        
        foreach (Mail* m, dir->getMailList()) {
            QDomElement mailElement = document.createElement("Mail");
            mailElement.setAttribute("senderName", m->getSenderName());
            mailElement.setAttribute("senderAddress", m->getSenderAddress());
            mailElement.setAttribute("recipientAddress", m->getRecipientAddress());
            mailElement.setAttribute("subject", m->getSubject());
            mailElement.setAttribute("text", Base64::toBase64(m->getText()));
            mailElement.setAttribute("timestamp", m->getTimeStamp().toString());
            mailElement.setAttribute("uid", m->getUid());
            mailElement.setAttribute("isRead", m->isRead());
            mailElement.setAttribute("directoryId", dir->getId());
            directoryElement.appendChild(mailElement);
        }
    }
    
    return document.toString();
}