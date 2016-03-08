/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MailView.cpp
 * Author: ckarner
 * 
 * Created on November 11, 2015, 10:40 AM
 */

#include "MailView.h"
#include "Mail.h"
#include <QString>
#include <QFormLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QSizePolicy>
#include "Fibonacci.h"
#include "Base64.h"
#include <QDebug>
#include "ContactPicker.h"

MailView::MailView(Mail* mail) {
    buildGui();
    setMail(mail);
}

void MailView::buildGui() {
    QFormLayout* formLayout = new QFormLayout();
    setLayout(formLayout);
    
    txtAddress = new QLineEdit();
    txtSubject = new QLineEdit();
    txtText = new QTextEdit();
    
    txtAddress->setObjectName("txtAddress");
    txtSubject->setObjectName("txtSubject");
    txtText->setObjectName("txtText");
    
    btnAddress = new QPushButton(this);
    lblSubject = new QLabel("Subject:");
    lblText = new QLabel("Text:");
    
    QSizePolicy policy = txtText->sizePolicy();
    policy.setVerticalStretch(1);
    txtText->setSizePolicy(policy);
    
    formLayout->addRow(btnAddress, txtAddress);
    formLayout->addRow(lblSubject, txtSubject);
    formLayout->addRow(lblText, txtText);
   
    txtAddress->setReadOnly(true);
    txtSubject->setReadOnly(true);
    txtText->setReadOnly(true);
}

void MailView::setMail(Mail* mail, bool reply) {    
    if (mail == 0) {
        txtAddress->setText("");
        txtSubject->setText("");
        txtText->setText("");
        
        connect(btnAddress, SIGNAL(clicked()), this, SLOT(openContacts()));
        
        btnAddress->setStyleSheet("text-align:left; text-decoration: underline");
    }
    else {
        txtAddress->setText(mail->getSenderAddress());
        
        if (mail->getSubject().startsWith("-=fib=-")) {
            Fibonacci fibonacci;
            txtSubject->setText(fibonacci.decrypt(mail->getSubject().mid(7)));
            txtText->setText(fibonacci.decrypt(mail->getText().replace("\r\n", "")));
        }
        else {
            txtSubject->setText(mail->getSubject());
            txtText->setText(mail->getText());
        }
        
        btnAddress->setStyleSheet("text-align:left");
    }
    
    bool readOnly = (mail != 0)?true:false;
    
    if (!reply) {
        txtAddress->setReadOnly(readOnly);
        txtSubject->setReadOnly(readOnly);
        txtText->setReadOnly(readOnly);
        btnAddress->setText((readOnly)?("From:"):("&To:"));
    }
    else {
        txtAddress->setReadOnly(!readOnly);
        txtSubject->setReadOnly(!readOnly);
        txtText->setReadOnly(!readOnly);
        btnAddress->setText("&To:");
    }
    
    if (btnAddress->text() == "&To:") {
        btnAddress->setStyleSheet("text-align:left; text-decoration: underline");
    }
    
    btnAddress->setFlat(true);
}

void MailView::openContacts() {
    if (btnAddress->text() == "&To:") {
        contactPicker->show();
    }
}

void MailView::contactSelected(QString mail) {
    txtAddress->setText(mail);
}

void MailView::setContactPicker(ContactPicker* contactPicker) {
    this->contactPicker = contactPicker;
    
    return;
}