/* 
 * File:   AddressBook.cpp
 * Author: ckarner
 * 
 * Created on October 15, 2015, 12:51 PM
 */

#include "AddressBook.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "ContactDialog.h"
#include <QHeaderView>

AddressBook::AddressBook(DataRepository *repository, QWidget *parent) : QWidget(parent) {
    this->repository = repository;
    this->model = new ContactTableModel(repository->getAllContacts(), this);
    
    buildGui();
        
    tblContacts->setModel(model);
}

void AddressBook::buildGui() {
    QHBoxLayout *hBox = new QHBoxLayout(this);
    
    QVBoxLayout *vBoxLeft = new QVBoxLayout();
    hBox->addLayout(vBoxLeft);
    
    QVBoxLayout *vBoxRight = new QVBoxLayout();
    hBox->addLayout(vBoxRight);
    
    tblContacts = new QTableView(this);
    vBoxLeft->addWidget(tblContacts);
    tblContacts->setSelectionMode(QAbstractItemView::SingleSelection);
    
    tblContacts->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    btnAdd = new QPushButton("Add");
    btnAdd->setIcon(QIcon::fromTheme("contact-new"));
    vBoxRight->addWidget(btnAdd);
    
    btnEdit = new QPushButton("Edit");
    btnEdit->setIcon(QIcon::fromTheme("accessories-text-editor"));
    vBoxRight->addWidget(btnEdit);
    
    btnDelete = new QPushButton("Delete");
    btnDelete->setIcon(QIcon::fromTheme("edit-delete"));
    vBoxRight->addWidget(btnDelete);
    
    vBoxRight->addStretch();
    
    tblContacts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
 
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteContact()));
    connect(tblContacts, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(passSelection()));
    connect(this, SIGNAL(editContactTriggered(Contact*)), this, SLOT(editContact(Contact*)));
    connect(repository, SIGNAL(contactsChanged()), this, SLOT(reloadData()));
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(passSelection()));
    
    return;
}

Contact* AddressBook::selected() {
    int index = tblContacts->currentIndex().row();
    if (index >= 0 && index < repository->getAllContacts().count()) {
        return repository->getAllContacts().at(index);
    }
    else {
        return NULL;
    }
}

void AddressBook::passSelection() {
    emit editContactTriggered(selected());
    return;
}

void AddressBook::reloadData() {
    model->setData(repository->getAllContacts());
}

void AddressBook::editContact(Contact *c) {
    if (c == NULL) {
        return;
    }
    
    ContactDialog contactDialog("Edit Contact", c, this);
    if (contactDialog.exec() == 1) {
        repository->save(c);
    }
}

void AddressBook::addContact() {
    Contact *c = new Contact();
    ContactDialog contactDialog("Add Contact", c, this);
    
    if (contactDialog.exec() == 1) {
        repository->save(c);
    }
    else {
        delete c;
    }
    
    return;
}

void AddressBook::deleteContact() {
    repository->remove(selected());
    
    return;
}