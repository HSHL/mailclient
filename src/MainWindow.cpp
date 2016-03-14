/* 
 * File:   MainWindow.cpp
 * Author: ckarner
 * 
 * Created on October 22, 2015, 11:30 AM
 */

#include "MainWindow.h"
#include <QMenu>
#include <QStatusBar>
#include <QMenuBar>
#include <QDebug>
#include <QDesktopWidget>
#include "SettingsDialog.h"
#include <QMessageBox>
#include "Fibonacci.h"

MainWindow::MainWindow() {
    this->mailCache = new MailCache();
    this->contactRepo = new ContactRepository("Contacts.xml");
    this->settings = new QSettings("mailClient.ini", QSettings::IniFormat, this);
    this->imap = new Imap(mailCache, settings);
    this->smtp = new Smtp(settings);
    
    buildGui();

    connect(contactRepo, SIGNAL(contactsChanged()), this, SLOT(saveData()));
    connect(mailCache, SIGNAL(refreshDirectories()), mailBox, SLOT(reloadDirectoryTree()));
    connect(smtp, SIGNAL(success(QString)), this, SLOT(sendSuccess(QString)));
    connect(smtp, SIGNAL(failure(QString)), this, SLOT(sendFailure(QString)));
    connect(imap, SIGNAL(connectedChanged()), this, SLOT(onConnectedChanged()));
    connect(mailBox, SIGNAL(showClose(bool)), this, SLOT(showClose(bool)));
}

void MainWindow::buildGui() {
    setWindowTitle("Mail Client");
    setWindowIcon(QIcon::fromTheme("mail-unread"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    mailBox = new MailBox(mailCache, contactRepo, imap, this);
//    contactPicker = new ContactPicker(repository, mailView);
//    mailView->setContactPicker(contactPicker);

    this->setCentralWidget(mailBox);
    statusBar()->showMessage(imap->isConnected() ? "Connected." : "Disconnected.");

    createActions();
    createMenus();
}

void MainWindow::createActions() {
    viewAddressBook = new QAction("&Address Book", this);
    connect(viewAddressBook, SIGNAL(triggered()), this, SLOT(showAddressBook()));

    viewMail = new QAction("&New Mail", this);
    connect(viewMail, SIGNAL(triggered()), this, SLOT(showMail()));

    viewSettings = new QAction("S&ettings", this);
    connect(viewSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

    refreshMails = new QAction("&Refresh Mails", this);
    connect(refreshMails, SIGNAL(triggered()), mailBox, SLOT(refreshMailsTriggered()));

    about = new QAction("&?", this);
    connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void MainWindow::createMenus() {
    menuBar()->addAction(viewMail);
    menuBar()->addAction(refreshMails);
    menuBar()->addAction(viewAddressBook);
    menuBar()->addAction(viewSettings);
    menuBar()->addAction(about);
}

void MainWindow::showAddressBook() {
    ContactsDialog *window = new ContactsDialog(contactRepo, this);
    window->show();
}

void MainWindow::showMail() {
    MailView window;
    if (window.exec() == QDialog::Accepted) {
        Mail *mail = window.getMail();
        smtp->sendMail(mail);
        
        // Todo: Add mail-object to sent-messages folder
        delete mail;
    }
}

void MainWindow::showSettings() {
    SettingsDialog settingsDialog(settings);
    settingsDialog.exec();
}

void MainWindow::sendSuccess(QString response) {
    QMessageBox(QMessageBox::Information, "Success", "Your mail has been sent.").exec();
}

void MainWindow::sendFailure(QString response) {
    QMessageBox(QMessageBox::Information, "Error", "A problem occured while sending your mail\r\n\r\n" + response).exec();
}

void MainWindow::onConnectedChanged() {
    statusBar()->showMessage(imap->isConnected() ? "Connected." : "Disconnected.");
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About", "Author: Christopher Karner (1141427)\r\n\r\nA simple mail client using IMAP and SMTP.\r\nTested with Outlook.com.");
}