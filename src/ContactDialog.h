/* 
 * File:   ContactDialog.h
 * Author: ckarner
 *
 * Created on October 27, 2015, 1:30 PM
 */

#ifndef CONTACTDIALOG_H
#define	CONTACTDIALOG_H

#include <QDialog>
#include "Contact.h"
#include <QLineEdit>
#include <QString>

class ContactDialog : public QDialog {
    Q_OBJECT
public:
    ContactDialog(const QString title, Contact* c, QWidget* parent);
private:
    Contact* c;
    QLineEdit* txtFirstName;
    QLineEdit* txtLastName;
    QLineEdit* txtMailAddress;
    
    void buildGui();
    
private slots:
    void onAccept();
};

#endif	/* CONTACTDIALOG_H */

