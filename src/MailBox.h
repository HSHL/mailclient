/* 
 * File:   MailBox.h
 * Author: ckarner
 *
 * Created on November 7, 2015, 9:03 PM
 */

#ifndef MAILBOX_H
#define	MAILBOX_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableView>
#include "MailTableModel.h"
#include "MailCache.h"
#include "ContactRepository.h"
#include "MailView.h"
#include <QMenu>
#include <QAction>
#include "ContactPicker.h"
#include <QTextEdit>
#include "Imap.h"

class MailBox : public QWidget {
    Q_OBJECT
    
public:
    MailBox(MailCache* dataRepo, ContactRepository *contactRepo, Imap *imap, QWidget* parent = 0);
    MailView* getMailView();
    
private:
    MailCache *mailCache;
    ContactRepository *contactRepo;
    Imap *imap;
    QTreeWidget* directoryTree;
    QTableView* tblMailView;
    MailTableModel* mailModel;
    Mail* selected() const;
    MailView* mailView;
    ContactPicker* contactPicker;
    QMenu* mailMenu;
    QAction* reply;
    QAction* forward;
    QAction* deleteMail;
    QAction* markAsUnseen;
    QTextEdit* txtTransmission;
    
public slots:
    void reloadDirectoryTree();
    void reloadMails();
    void replyTriggered();
    void forwardTriggered();
    void deleteMailTriggered();
    void markAsUnseenTriggered();
    void mailContextMenu(const QPoint&point);
    void refreshMailsTriggered();
    
private slots:
    void showMail();
    void buildDiretoryTree();
    void directoryAdded(Directory *dir);
    
signals:
    void directoriesReady();
    void showClose(bool value = true);
};

#endif	/* MAILBOX_H */