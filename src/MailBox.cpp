/* 
 * File:   MailBox.cpp
 * Author: ckarner
 * 
 * Created on November 7, 2015, 9:03 PM
 */

#include "MailBox.h"
#include <QHBoxLayout>
#include "Mail.h"
#include <QSizePolicy>
#include <QList>
#include <QDateTime>
#include "MailView.h"
#include "ContactsDialog.h"
#include <QHeaderView>
#include <QString>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFont>
#include <QMessageBox>
#include "Logger.h"

MailBox::MailBox(MailCache* mailCache, ContactRepository *contactRepo, Imap *imap, QWidget* parent) : QWidget(parent) {
    Logger::debug("MailBox.constructor");
    
    this->mailCache = mailCache;
    this->contactRepo = contactRepo;
    this->imap = imap;
    
    QHBoxLayout *hBox = new QHBoxLayout(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    directoryTree = new QTreeWidget(this);
    directoryTree->header()->close();
    hBox->addWidget(directoryTree);    
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(0.5);
    directoryTree->setSizePolicy(spLeft);

    QVBoxLayout *vBox = new QVBoxLayout();
    QHBoxLayout *smallHBox = new QHBoxLayout();
    vBox->addLayout(smallHBox);
    hBox->addLayout(vBox);
    
    tblMailView = new QTableView();
    smallHBox->addWidget(tblMailView);
    
    QList<Mail*> list;
    mailModel = new MailTableModel(list, this);
    tblMailView->setModel(mailModel);
    
    tblMailView->resizeColumnToContents(0);
    tblMailView->resizeColumnToContents(1);
    tblMailView->resizeColumnToContents(3);
    tblMailView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tblMailView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblMailView->setShowGrid(false);
    tblMailView->setSelectionMode(QAbstractItemView::SingleSelection);
        
    mailView = new MailView();
    contactPicker = new ContactPicker(contactRepo, mailView);
    mailView->setContactPicker(contactPicker);    
    
    smallHBox->addWidget(mailView);
    mailView->close();
    
    sizePolicy.setHorizontalStretch(1);
    
    QSizePolicy spBottom(QSizePolicy::Preferred, QSizePolicy::Preferred);
    txtTransmission = new QTextEdit(this);
    txtTransmission->setSizePolicy(spBottom);
    txtTransmission->setVisible(false);
    vBox->addWidget(txtTransmission);
    
    txtTransmission->setFont(QFont("Courier", 9));
    
    tblMailView->setContextMenuPolicy(Qt::CustomContextMenu);
    
    mailMenu = new QMenu(this);
    reply = new QAction("Reply", this);
    forward = new QAction("Forward", this);
    deleteMail = new QAction("Delete mail", this);
    markAsUnseen = new QAction("Mark as unseen", this);

    reply->setIcon(QIcon::fromTheme("mail-reply-sender"));
    reply->setIconVisibleInMenu(true);
    
    forward->setIcon(QIcon::fromTheme("mail-forward"));
    forward->setIconVisibleInMenu(true);
    
    deleteMail->setIcon(QIcon::fromTheme("edit-delete"));
    deleteMail->setIconVisibleInMenu(true);
    
    markAsUnseen->setIcon(QIcon::fromTheme("mail-mark-unread"));
    markAsUnseen->setIconVisibleInMenu(true);
    
    mailMenu->addAction(reply);
    mailMenu->addAction(forward);
    mailMenu->addAction(markAsUnseen);
    mailMenu->addAction(deleteMail);
    
    connect(mailCache, SIGNAL(directoryAdded(Directory*)), this, SLOT(directoryAdded(Directory*)));
    connect(directoryTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(directorySelected(QTreeWidgetItem*)));
    
    connect(reply, SIGNAL(triggered()), this, SLOT(replyTriggered()));
    connect(forward, SIGNAL(triggered()), this, SLOT(forwardTriggered()));
    connect(deleteMail, SIGNAL(triggered()), this, SLOT(deleteMailTriggered()));
    connect(markAsUnseen, SIGNAL(triggered()), this, SLOT(markAsUnseenTriggered()));
}

void MailBox::reloadMails() {
    Logger::debug("MailBox.reloadMails");
//    if (directoryTree->currentIndex().isValid()) {
//        mailModel->setData(dirModel->getData(directoryTree->currentIndex())->getMailList());
//        tblMailView->resizeColumnToContents(0);
//        tblMailView->resizeColumnToContents(1);
//        tblMailView->resizeColumnToContents(3);
//        tblMailView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
//        tblMailView->reset();
//    }
}

void MailBox::showMail() {
    Logger::debug("MailBox.showMail");
//    mailView->setMail(selected());
//    mailView->show();
//    emit showClose();
//    
//    if (!selected()->isRead()) {
//        selected()->readMail();
//        if (imap->isConnected()) {
//            imap->readMail(selected(), dirModel->getData(directoryTree->currentIndex()));
//        }
//    }
}

Mail* MailBox::selected() const {
    int index = tblMailView->currentIndex().row();
    
    if (index >= 0 && index < mailModel->getData().count()) {
        return mailModel->getData().at(index);
    }
    else {
        return NULL;
    }
}

void MailBox::mailContextMenu(const QPoint& point) {
    mailMenu->exec(QCursor::pos());
}

void MailBox::replyTriggered() {
    Mail *mail = new Mail();
    mail->setSenderAddress(selected()->getSenderAddress());
    mail->setSubject("Re: " + selected()->getSubject());
    mail->setText("\r\n\r\n--------------------\r\n\r\n" + selected()->getText());
    mailView->setMail(mail, true);
    
    delete mail;
}

void MailBox::forwardTriggered() {
    Mail *mail = new Mail();
    
    mail->setSenderAddress("");
    mail->setSubject("Fw: " + selected()->getSubject());
    mail->setText("\r\n\r\n--------------------\r\n\r\n" + selected()->getText());
    
    mailView->setMail(mail, true);
    
    delete mail;
}

void MailBox::deleteMailTriggered() {
//    if (imap->isConnected()) {
//        imap->deleteMail(selected(), dirModel->getData(directoryTree->currentIndex()));
//        mailModel->removeRows(tblMailView->currentIndex().row(), 1);
//    }
}

void MailBox::markAsUnseenTriggered() {
//    if (imap->isConnected()) {
//        imap->unreadMail(selected(), dirModel->getData(directoryTree->currentIndex()));
//        selected()->unreadMail();
//    }
}

void MailBox::refreshMailsTriggered() {
    if (!imap->isConnected())
        imap->connect();
}

void MailBox::reloadDirectoryTree() {
//    mailModel->clear();
//    dirModel->changeData(this->mailCache->getDirectoriesHierarchically());
//    directoryTree->reset();
//    directoryTree->expandAll();
//    
//    QModelIndex first = dirModel->index(0, 0, QModelIndex());
//    directoryTree->setCurrentIndex(first);
//    
//    emit directoriesReady();
}

void MailBox::directoryAdded(Directory* dir) {
    if (dir->getParentDirectory() == NULL) {
        QTreeWidgetItem *item = new QTreeWidgetItem(directoryTree);
        item->setText(0, dir->getName());
        item->setText(1, dir->getPath());
    }
}

void MailBox::directorySelected(QTreeWidgetItem* item) {
    
}
