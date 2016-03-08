/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SettingsDialog.cpp
 * Author: ckarner
 * 
 * Created on December 11, 2015, 11:38 AM
 */

#include "SettingsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QDebug>
#include "Settings.h"

SettingsDialog::SettingsDialog(Settings* s, QWidget* parent) : QDialog(parent) {
    settings = s;
    
    buildGui();
}

void SettingsDialog::buildGui() {
    setWindowIcon(QIcon::fromTheme("preferences-system"));
    setWindowTitle("Settings");
    
    QVBoxLayout* basicLayout = new QVBoxLayout(this);
    
    QHBoxLayout* formBox = new QHBoxLayout();
    
    basicLayout->addLayout(formBox);
    
    QGroupBox* imapBox = new QGroupBox(tr("IMAP-Settings"));
    QFormLayout* imapForm = new QFormLayout();
    
    formBox->addWidget(imapBox);
    imapBox->setLayout(imapForm);
    
    imapLogin = new QLineEdit();
    imapPassword = new QLineEdit();
    imapHost = new QLineEdit();
    imapPort = new QLineEdit();
    imapTimeout = new QLineEdit();
    
    imapPassword->setEchoMode(QLineEdit::Password);
    
    imapForm->addRow(tr("User"), imapLogin);
    imapForm->addRow(tr("Password"), imapPassword);
    imapForm->addRow(tr("Host"), imapHost);
    imapForm->addRow(tr("Port"), imapPort);
    imapForm->addRow(tr("Timeout"), imapTimeout);
    
    
    QGroupBox* smtpBox = new QGroupBox(tr("SMTP-Settings"));
    QFormLayout* smtpForm = new QFormLayout();
    
    formBox->addWidget(smtpBox);
    smtpBox->setLayout(smtpForm);
    
    smtpLogin = new QLineEdit();
    smtpPassword = new QLineEdit();
    smtpHost = new QLineEdit();
    smtpPort = new QLineEdit();
    smtpTls = new QCheckBox();
    
    smtpPassword->setEchoMode(QLineEdit::Password);
    
    smtpForm->addRow(tr("User"), smtpLogin);
    smtpForm->addRow(tr("Password"), smtpPassword);
    smtpForm->addRow(tr("Host"), smtpHost);
    smtpForm->addRow(tr("Port"), smtpPort);
    smtpForm->addRow(tr("Use TLS"), smtpTls);
    
    QHBoxLayout *buttonBox = new QHBoxLayout();
    
    basicLayout->addLayout(buttonBox);
    
    QPushButton *btnOK = new QPushButton("OK");
    QPushButton *btnCancel = new QPushButton("Cancel");
    
    buttonBox->addStretch();
    buttonBox->addWidget(btnOK);
    buttonBox->addWidget(btnCancel);

    
    connect(btnOK, SIGNAL(clicked()), this, SLOT(onAccept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    
    
    imapLogin->setText(settings->getImapLogin());
    imapPassword->setText(settings->getImapPassword());
    imapHost->setText(settings->getImapHost());
    imapPort->setText(QString::number(settings->getImapPort()));
    imapTimeout->setText(QString::number(settings->getImapTimeout()));
    
    smtpLogin->setText(settings->getSmtpLogin());
    smtpPassword->setText(settings->getSmtpPassword());
    smtpHost->setText(settings->getSmtpHost());
    smtpPort->setText(QString::number(settings->getSmtpPort()));
    smtpTls->setChecked(settings->useTls());
    
    return;
}

void SettingsDialog::onAccept() {
    bool ok = false;
    settings->setImapLogin(imapLogin->text());
    settings->setImapPassword(imapPassword->text());
    settings->setImapHost(imapHost->text());
    settings->setImapPort(imapPort->text().toUInt(&ok));
    settings->setImapTimeout(imapTimeout->text().toUInt(&ok));
    
    settings->setSmtpLogin(smtpLogin->text());
    settings->setSmtpPassword(smtpPassword->text());
    settings->setSmtpHost(smtpHost->text());
    settings->setSmtpPort(smtpPort->text().toUInt(&ok));
    settings->setTls(smtpTls->isChecked());
    
    accept();
    
    return;
}
