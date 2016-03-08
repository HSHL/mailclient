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
#include "AddressBook.h"
#include <QHeaderView>
#include <QString>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFont>
#include <QMessageBox>

void MailBox::reloadDirectoryTree() {
    mailModel->clear();
    dirModel->changeData(this->repository->getDirectoriesHierarchically());
    directoryTree->reset();
    directoryTree->expandAll();
    
    QModelIndex first = dirModel->index(0, 0, QModelIndex());
    directoryTree->setCurrentIndex(first);
    
    emit directoriesReady();
}

MailBox::MailBox(DataRepository* repository, QWidget* parent) : QWidget(parent) {
    this->repository = repository;
    
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
    connect(repository->getInterface()->getImap(), SIGNAL(fetchCompleted()), this, SLOT(reloadMails()));
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
        
        if (repository->getInterface()->getImap()->isConnected()) {            
            repository->getInterface()->getImap()->selectDirectory(dirModel->getData(current));
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
        if (repository->getInterface()->getImap()->isConnected()) {
            repository->getInterface()->getImap()->readMail(selected(), dirModel->getData(directoryTree->currentIndex()));
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
    if (repository->getInterface()->getImap()->isConnected()) {
        repository->getInterface()->getImap()->deleteMail(selected(), dirModel->getData(directoryTree->currentIndex()));
        mailModel->removeRows(tblMailView->currentIndex().row(), 1);
    }
}

void MailBox::markAsUnseenTriggered() {
    if (repository->getInterface()->getImap()->isConnected()) {
        repository->getInterface()->getImap()->unreadMail(selected(), dirModel->getData(directoryTree->currentIndex()));
        selected()->unreadMail();
    }
}

MailView* MailBox::getMailView() {
    return this->mailView;
}

void MailBox::showTransmission(int value) {
    txtTransmission->setVisible(value);
    
    if (value != 0) {
        connect(repository->getInterface()->getImap(), SIGNAL(printLine(QString)), this, SLOT(printLine(QString)));
        connect(repository->getInterface()->getSmtp(), SIGNAL(printLine(QString)), this, SLOT(printLine(QString)));
        QMessageBox(QMessageBox::Information, "Warning", "Activating this function may cause performance issues.").exec();
    }
    else {
        this->disconnect(repository->getInterface()->getImap(), SIGNAL(printLine(QString)), 0, 0);
        this->disconnect(repository->getInterface()->getSmtp(), SIGNAL(printLine(QString)), 0, 0);
    }
}

void MailBox::printLine(QString s) {    
    txtTransmission->setPlainText(txtTransmission->toPlainText().append(s));
    txtTransmission->verticalScrollBar()->setValue(txtTransmission->verticalScrollBar()->maximum());
}

void MailBox::refreshMailsTriggered() {
    if (repository->getInterface()->getImap()->isConnected()) {            
            repository->getInterface()->getImap()->selectDirectory(dirModel->getData(directoryTree->currentIndex()));
    }
}