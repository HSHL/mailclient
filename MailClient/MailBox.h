/* 
 * File:   MailBox.h
 * Author: ckarner
 *
 * Created on November 7, 2015, 9:03 PM
 */

#ifndef MAILBOX_H
#define	MAILBOX_H

#include <QWidget>
#include <QTreeView>
#include <QTableView>
#include "DirectoryTreeModel.h"
#include "MailTableModel.h"
#include "DataRepository.h"
#include <QModelIndex>
#include "MailView.h"
#include <QMenu>
#include <QAction>
#include "ContactPicker.h"
#include <QTextEdit>

class MailBox : public QWidget {
    Q_OBJECT
public:
    MailBox(DataRepository* repository, QWidget* parent = 0);
    MailView* getMailView();
private:
    QTreeView* directoryTree;
    QTableView* tblMailView;
    
    DirectoryTreeModel* dirModel;
    MailTableModel* mailModel;
    DataRepository* repository;
    
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
    void currentDirectoryChanged(const QModelIndex& current, const QModelIndex& previous);
    void reloadMails();
    void replyTriggered();
    void forwardTriggered();
    void deleteMailTriggered();
    void markAsUnseenTriggered();
    void mailContextMenu(const QPoint&point);
    void showTransmission(int value);
    void printLine(QString s);
    void refreshMailsTriggered();
    
private slots:
    void showMail();
    
signals:
    void directoriesReady();
    void showClose(bool value = true);
};

#endif	/* MAILBOX_H */

