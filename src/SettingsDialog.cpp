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

SettingsDialog::SettingsDialog(QSettings* settings, QWidget* parent) : QDialog(parent) {
    this->settings = settings;
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

    imapLogin->setText(settings->value("IMAP/login").toString());
    imapPassword->setText(settings->value("IMAP/password").toString());
    imapHost->setText(settings->value("IMAP/host").toString());
    imapPort->setText(settings->value("IMAP/port").toString());
    imapTimeout->setText(settings->value("IMAP/timeout").toString());

    smtpLogin->setText(settings->value("SMTP/login").toString());
    smtpPassword->setText(settings->value("SMTP/password").toString());
    smtpHost->setText(settings->value("SMTP/host").toString());
    smtpPort->setText(settings->value("SMTP/port").toString());
    smtpTls->setChecked(settings->value("SMTP/tls").toBool());
}

void SettingsDialog::onAccept() {
    settings->setValue("IMAP/login", imapLogin->text());
    settings->setValue("IMAP/password", imapPassword->text());
    settings->setValue("IMAP/host", imapHost->text());
    settings->setValue("IMAP/port", imapPort->text());
    settings->setValue("IMAP/timeout", imapTimeout->text());

    settings->setValue("SMTP/login", smtpLogin->text());
    settings->setValue("SMTP/password", smtpPassword->text());
    settings->setValue("SMTP/host", smtpHost->text());
    settings->setValue("SMTP/port", smtpPort->text());
    settings->setValue("SMTP/tls", smtpTls->isChecked());

    accept();
}
