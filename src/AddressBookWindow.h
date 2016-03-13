/* 
 * File:   AddressBook.h
 * Author: ckarner
 *
 * Created on October 15, 2015, 12:51 PM
 */

#ifndef ADDRESSBOOK_H
#define	ADDRESSBOOK_H

#include <QDialog>
#include "ContactTableModel.h"
#include "Contact.h"
#include <QList>
#include <QTableView>
#include "DataRepository.h"
#include <QPushButton>

class AddressBookWindow : public QDialog {
    Q_OBJECT

public:
    AddressBookWindow(DataRepository* repository, QWidget* parent = 0);

private:
    DataRepository* repository;
    ContactTableModel* model;
    QTableView* tblContacts;
    Contact* selected();

    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnEdit;

    void buildGui();

private slots:
    void passSelection();
    void reloadData();
    void editContact(Contact *c);
    void addContact();
    void deleteContact();

signals:
    void editContactTriggered(Contact*);
    void saveData();
};

#endif	/* ADDRESSBOOK_H */