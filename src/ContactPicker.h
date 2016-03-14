/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactPicker.h
 * Author: ckarner
 *
 * Created on December 30, 2015, 10:53 PM
 */

#ifndef CONTACTPICKER_H
#define CONTACTPICKER_H

#include <QDialog>
#include "ContactTableModel.h"
#include "Contact.h"
#include "ContactRepository.h"
#include <QTableView>

class MailView;

class ContactPicker : public QDialog {
    Q_OBJECT
    
public:
    ContactPicker(ContactRepository* repository, MailView* mailView = 0, QWidget* parent = 0);

private:
    ContactRepository* repository;
    ContactTableModel* model;
    QTableView* tblContacts;
    Contact* selected() const;
    MailView* mailView;
    void showEvent(QShowEvent *event );
    void buildGui();
    
private slots:
    void passSelection();    

    signals:
    void contactSelected(QString mail);
};

#endif /* CONTACTPICKER_H */