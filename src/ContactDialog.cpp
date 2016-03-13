/* 
 * File:   ContactDialog.cpp
 * Author: ckarner
 * 
 * Created on October 27, 2015, 1:30 PM
 */

#include "ContactDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include "Contact.h"
#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QHBoxLayout>
#include <QSizePolicy>

ContactDialog::ContactDialog(const QString title, Contact* c, QWidget* parent) : QDialog(parent) {
    this->c = c;
    
    buildGui();
    
    setWindowTitle(title);
    
    txtFirstName->setText(c->firstName());
    txtLastName->setText(c->lastName());
    txtMailAddress->setText(c->mailAddress());
}

void ContactDialog::buildGui() {  
    setWindowIcon(QIcon::fromTheme("address-book-new"));
    QFormLayout *formLayout = new QFormLayout(this);
    
    txtFirstName = new QLineEdit();
    txtLastName = new QLineEdit();
    txtMailAddress = new QLineEdit();
    
    QHBoxLayout *hBox = new QHBoxLayout();
    QPushButton *btnOk = new QPushButton("OK");
    QPushButton *btnCancel = new QPushButton("Cancel");
    
    hBox->addWidget(btnOk);
    hBox->addWidget(btnCancel);
    
    formLayout->addRow(tr("First name"), txtFirstName);
    formLayout->addRow(tr("Last name"), txtLastName);
    formLayout->addRow(tr("Mail address"), txtMailAddress);
    formLayout->addRow(tr(""), hBox);
    
    setLayout(formLayout);
    
    connect(btnOk, SIGNAL(clicked()), this, SLOT(onAccept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    
    return;
}

void ContactDialog::onAccept() {
    if ((txtFirstName->text() != "") && (txtMailAddress->text() != "")) {
        c->firstName(txtFirstName->text());
        c->lastName(txtLastName->text());
        c->mailAddress(txtMailAddress->text());
        accept();
    }
    else {
        QMessageBox::warning(this, "Information", "Please enter at least the first name and the mail address.");
    }
    
    return;
}