/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactPicker.cpp
 * Author: ckarner
 * 
 * Created on December 30, 2015, 10:53 PM
 */

#include "ContactPicker.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include "MailView.h"

ContactPicker::ContactPicker(ContactRepository* repository, MailView* mailView, QWidget* parent) : QDialog(parent) {
    setWindowIcon(QIcon::fromTheme("x-office-address-book"));
    this->repository = repository;
    this->mailView = mailView;
    QHBoxLayout *hBox = new QHBoxLayout(this);
    
    tblContacts = new QTableView(this);
    hBox->addWidget(tblContacts);
    tblContacts->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblContacts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   
    
    connect(tblContacts, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(passSelection()));
    connect(this, SIGNAL(contactSelected(QString)), this->mailView, SLOT(contactSelected(QString)));
}

Contact* ContactPicker::selected() const {
    int index = tblContacts->currentIndex().row();
    if (index >= 0 && index < repository->getAllContacts().count()) {
        return repository->getAllContacts().at(index);
    }
    else {
        return NULL;
    }
}

void ContactPicker::passSelection() {
    emit contactSelected(selected()->mailAddress());
    
    this->close();
    
    return;
}

void ContactPicker::showEvent(QShowEvent*) {
    this->model = new ContactTableModel(repository->getAllContacts(), this, true);
    tblContacts->setModel(model);
    
    return;
}