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
#include "XmlWriter.h"
#include <QDesktopWidget>
#include "SettingsDialog.h"
#include <QMessageBox>
#include "Fibonacci.h"

MainWindow::MainWindow(DataRepository *repository) {    
    this->repository = repository;
    
    buildGui();
    
    connect(repository, SIGNAL(contactsChanged()), this, SLOT(saveData()));
    connect(addressBook, SIGNAL(saveData()), this, SLOT(saveData()));    
    connect(repository, SIGNAL(refreshDirectories()), mailBox, SLOT(reloadDirectoryTree()));
    connect(repository->getInterface()->getSmtp(), SIGNAL(success(QString)), this, SLOT(sendSuccess(QString)));
    connect(repository->getInterface()->getSmtp(), SIGNAL(failure(QString)), this, SLOT(sendFailure(QString)));
    connect(this, SIGNAL(settingsChanged()), repository, SLOT(updateSettings()));
    connect(repository->getInterface()->getImap(), SIGNAL(connectedChanged()), this, SLOT(onConnectedChanged()));
    connect(mailBox, SIGNAL(showClose(bool)), this, SLOT(showClose(bool)));
    connect(chkShowCheckbox, SIGNAL(stateChanged(int)), mailBox, SLOT(showTransmission(int)));
}

void MainWindow::buildGui() {
    setWindowTitle("Mail Client");
    setWindowIcon(QIcon::fromTheme("mail-unread"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    
    addressBook = new AddressBook(repository, this);
    mailBox = new MailBox(repository, this);
    mailView = new MailView();
    contactPicker = new ContactPicker(repository, mailView);
    mailView->setContactPicker(contactPicker);
    
    stackedWidget = new QStackedWidget();
    
    stackedWidget->addWidget(mailBox);
    stackedWidget->addWidget(addressBook);
    stackedWidget->addWidget(mailView);
    
    this->setCentralWidget(stackedWidget);
    
    stackedWidget->setCurrentWidget(mailBox);
    
    statusBar()->showMessage((repository->getInterface()->getImap()->isConnected())?("Connected."):("Disconnected."));
    
    chkShowCheckbox = new QCheckBox("Show transmission", this);
    statusBar()->addPermanentWidget(chkShowCheckbox);
    
    createActions();
    createMenus();
    
    return;
}

void MainWindow::createActions() {
    viewAddressBook = new QAction("&Address Book", this);
    connect(viewAddressBook, SIGNAL(triggered()), this, SLOT(showAddressBook()));
    
    viewMailBox = new QAction("&Mail Box", this);
    connect(viewMailBox, SIGNAL(triggered()), this, SLOT(showMailBox()));
    
    viewMail = new QAction("&New Mail", this);
    connect(viewMail, SIGNAL(triggered()), this, SLOT(showMail()));
    
    viewSettings = new QAction("S&ettings", this);
    connect(viewSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
    
    refreshMails = new QAction("&Refresh Mails",this);
    connect(refreshMails, SIGNAL(triggered()), mailBox, SLOT(refreshMailsTriggered()));
    
    sendMail = new QAction("&Send", this);
    connect(sendMail, SIGNAL(triggered()), this, SLOT(startTransmission()));
    
    clear = new QAction("&Clear", this);
    connect(clear, SIGNAL(triggered()), this, SLOT(clearMail()));
    
    closeCurrent = new QAction("Cl&ose", this);
    connect(closeCurrent, SIGNAL(triggered()), this, SLOT(closeCurrentWidget()));
    
    about = new QAction("&?", this);
    connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));
    
    return;
}

void MainWindow::createMenus() {
    menuBar()->addAction(viewMailBox);
    menuBar()->addAction(viewAddressBook);
    menuBar()->addAction(viewMail);
    menuBar()->addAction(viewSettings);
    menuBar()->addAction(refreshMails);
    menuBar()->addAction(sendMail);
    menuBar()->addAction(clear);
    menuBar()->addAction(closeCurrent);
    menuBar()->addAction(about);
    
    sendMail->setVisible(false);
    clear->setVisible(false);
    closeCurrent->setVisible(false);
    
    return;
}

void MainWindow::showAddressBook() {
    qDebug() << "Address Book";
    
    stackedWidget->setCurrentWidget(addressBook);
    
    viewAddressBook->setVisible(true);
    viewMailBox->setVisible(true);
    viewMail->setVisible(true);
    viewSettings->setVisible(true);
    refreshMails->setVisible(false);
    sendMail->setVisible(false);
    clear->setVisible(false);
    closeCurrent->setVisible(true);
    about->setVisible(true);
    
    return;
}

void MainWindow::showMailBox() {
    qDebug() << "Mail Box";
    
    stackedWidget->setCurrentWidget(mailBox);
    closeCurrent->setVisible(false);
    
    viewAddressBook->setVisible(true);
    viewMailBox->setVisible(true);
    viewMail->setVisible(true);
    viewSettings->setVisible(true);
    refreshMails->setVisible(true);
    sendMail->setVisible(false);
    clear->setVisible(false);
    closeCurrent->setVisible(false);
    about->setVisible(true);
    
    return;
}

void MainWindow::showMail() {
    qDebug() << "Mail";
    
    mailView->setMail();
    stackedWidget->setCurrentWidget(mailView);
    
    viewAddressBook->setVisible(false);
    viewMailBox->setVisible(false);
    viewMail->setVisible(false);
    viewSettings->setVisible(false);
    refreshMails->setVisible(false);
    sendMail->setVisible(true);
    clear->setVisible(true);
    closeCurrent->setVisible(true);
    about->setVisible(true);
    
    return;
}

void MainWindow::showSettings() {
    qDebug() << "Settings";
    
    SettingsDialog settingsDialog(repository->getSettings());
    
    if (settingsDialog.exec() == 1) {
        repository->clearDirectories();
        emit settingsChanged();
    }
    
    return;
}

void MainWindow::closeCurrentWidget() {
    mailBox->getMailView()->hide();
    showMailBox();
    
    return;
}

void MainWindow::saveData() {
    XmlWriter writer(this->repository);
    writer.write();
    
    return;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    emit saveData();
    
    return;
}

void MainWindow::startTransmission() {
    QString recipient = mailView->findChild<QLineEdit*>("txtAddress")->text();
    QString subject = mailView->findChild<QLineEdit*>("txtSubject")->text();
    QString text = mailView->findChild<QTextEdit*>("txtText")->toPlainText();
    
    if (QMessageBox(QMessageBox::Question, "Encryption", "Do you want to send this message encrypted?", QMessageBox::Yes|QMessageBox::No).exec() == QMessageBox::Yes) {
        Fibonacci fibonacci;
        subject = "-=fib=-" + fibonacci.encrypt(subject);
        text = fibonacci.encrypt(text);
    }
    
    repository->getInterface()->getSmtp()->sendMail(recipient, subject, text);
    
    return;
}

void MainWindow::clearMail() {
    mailView->findChild<QLineEdit*>("txtAddress")->clear();
    mailView->findChild<QLineEdit*>("txtSubject")->clear();
    mailView->findChild<QTextEdit*>("txtText")->clear();
    
    return;
}

void MainWindow::sendSuccess(QString response) {
    QMessageBox(QMessageBox::Information, "Success", "Your mail has been sent.").exec();
    
    return;
}

void MainWindow::sendFailure(QString response) {
    QMessageBox(QMessageBox::Information, "Error", "A problem occured while sending your mail\r\n\r\n" + response).exec();

    return;
}

void MainWindow::onConnectedChanged() {
    statusBar()->showMessage((repository->getInterface()->getImap()->isConnected())?("Connected."):("Disconnected."));
    
    return;
}

void MainWindow::showClose(bool value) {
    closeCurrent->setVisible(value);
    
    return;
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About", "Author: Christopher Karner (1141427)\r\n\r\nA simple mail client using IMAP and SMTP.\r\nTested with Outlook.com.");
    
    return;
}