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
#include "AddressBookWindow.h"
#include <QHeaderView>
#include <QString>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFont>
#include <QMessageBox>

MailBox::MailBox(DataRepository* repository, Imap *imap, QWidget* parent) : QWidget(parent) {
    this->repository = repository;
    this->imap = imap;
    
    QHBoxLayout *hBox = new QHBoxLayout(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    directoryTree = new QTreeView(this);
    hBox->addWidget(directoryTree);    
    
    dirModel = new DirectoryTreeModel(this->repository->getDirectoriesHierarchically());
    directoryTree->setModel(dirModel);
    directoryTree->expandAll();
    
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
    contactPicker = new ContactPicker(repository, mailView);
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
    
    connect(directoryTree->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(currentDirectoryChanged(QModelIndex, QModelIndex)));
    connect(imap, SIGNAL(fetchCompleted()), this, SLOT(reloadMails()));
    connect(tblMailView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(showMail()));
    connect(tblMailView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(mailContextMenu(QPoint)));
    connect(reply, SIGNAL(triggered()), this, SLOT(replyTriggered()));
    connect(forward, SIGNAL(triggered()), this, SLOT(forwardTriggered()));
    connect(deleteMail, SIGNAL(triggered()), this, SLOT(deleteMailTriggered()));
    connect(markAsUnseen, SIGNAL(triggered()), this, SLOT(markAsUnseenTriggered()));
}

void MailBox::currentDirectoryChanged(const QModelIndex& current, const QModelIndex& previous) {
    if (directoryTree->currentIndex().isValid()) {
        if (mailView->isVisible())
            emit showClose(false);
        
        mailView->close();
        
        if (imap->isConnected()) {            
            imap->selectDirectory(dirModel->getData(current));
        }
        
        reloadMails();        
    }
}

void MailBox::reloadMails() {
    if (directoryTree->currentIndex().isValid()) {
        mailModel->setData(dirModel->getData(directoryTree->currentIndex())->getMailList());
        tblMailView->resizeColumnToContents(0);
        tblMailView->resizeColumnToContents(1);
        tblMailView->resizeColumnToContents(3);
        tblMailView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        tblMailView->reset();
    }
}

void MailBox::showMail() {
    mailView->setMail(selected());
    mailView->show();
    emit showClose();
    
    if (!selected()->isRead()) {
        selected()->readMail();
        if (imap->isConnected()) {
            imap->readMail(selected(), dirModel->getData(directoryTree->currentIndex()));
        }
    }
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
    if (imap->isConnected()) {
        imap->deleteMail(selected(), dirModel->getData(directoryTree->currentIndex()));
        mailModel->removeRows(tblMailView->currentIndex().row(), 1);
    }
}

void MailBox::markAsUnseenTriggered() {
    if (imap->isConnected()) {
        imap->unreadMail(selected(), dirModel->getData(directoryTree->currentIndex()));
        selected()->unreadMail();
    }
}

MailView* MailBox::getMailView() {
    return this->mailView;
}

void MailBox::refreshMailsTriggered() {
    if (!imap->isConnected())
        imap->connect();
    
    if (imap->isConnected())
        imap->selectDirectory(dirModel->getData(directoryTree->currentIndex()));
}

void MailBox::reloadDirectoryTree() {
    mailModel->clear();
    dirModel->changeData(this->repository->getDirectoriesHierarchically());
    directoryTree->reset();
    directoryTree->expandAll();
    
    QModelIndex first = dirModel->index(0, 0, QModelIndex());
    directoryTree->setCurrentIndex(first);
    
    emit directoriesReady();
}