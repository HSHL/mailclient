/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SettingsDialog.h
 * Author: ckarner
 *
 * Created on December 11, 2015, 11:38 AM
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QLineEdit>
#include <QCheckBox>

class SettingsDialog : public QDialog {
    Q_OBJECT
    
public:
    SettingsDialog(QSettings* settings, QWidget* parent = 0);
    
private:
    void buildGui();
    
    QLineEdit* imapLogin;
    QLineEdit* imapPassword;
    QLineEdit* imapHost;
    QLineEdit* imapPort;
    QLineEdit* imapTimeout;
    
    QLineEdit* smtpLogin;
    QLineEdit* smtpPassword;
    QLineEdit* smtpHost;
    QLineEdit* smtpPort;
    QCheckBox* smtpTls;
    
    QSettings* settings;
private slots:
    void onAccept();
};

#endif /* SETTINGSDIALOG_H */