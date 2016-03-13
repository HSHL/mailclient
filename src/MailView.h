/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MailView.h
 * Author: ckarner
 *
 * Created on November 11, 2015, 10:40 AM
 */

#ifndef MAILVIEW_H
#define MAILVIEW_H

#include "Mail.h"
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include "ContactPicker.h"

class MailView : public QDialog {
    Q_OBJECT

public:
    MailView(Mail* mail = 0);
    void setMail(Mail* mail = 0, bool reply = false);
    Mail* getMail();
    void setContactPicker(ContactPicker* contactPicker);
    
private:
    void buildGui();
    Mail *mail;
    QPushButton* btnAddress;
    QLabel* lblSubject;
    QLabel* lblText;
    QLineEdit* txtAddress;
    QLineEdit* txtSubject;
    QTextEdit* txtText;
    ContactPicker* contactPicker;
    
private slots:
    void send();
    void cancel();
    void openContacts();    
    void contactSelected(QString mail);
};

#endif /* MAILVIEW_H */