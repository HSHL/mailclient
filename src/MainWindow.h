/* 
 * File:   MainWindow.h
 * Author: ckarner
 *
 * Created on October 22, 2015, 11:30 AM
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QMenu>
#include "MailCache.h"
#include "ContactRepository.h"
#include "ContactsDialog.h"
#include "MailBox.h"
#include "MailView.h"
#include <QCloseEvent>
#include "ContactPicker.h"
#include <QCheckBox>
#include "Imap.h"
#include "Smtp.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow();
    
private:
    MailCache* mailCache;
    ContactRepository *contactRepo;
    QSettings *settings;
    Imap *imap;
    Smtp *smtp;
    QMenu* fileMenu;
    QAction* viewAddressBook;
    QAction* viewMail;
    QAction* refreshMails;
    QAction* viewSettings;
    QAction* about;
    MailBox* mailBox;
    ContactPicker* contactPicker;

    void createMenus();
    void createActions();
    void buildGui();

private slots:
    void showAddressBook();
    void showMail();
    void showAbout();
    void showSettings();
    void sendSuccess(QString response);
    void sendFailure(QString response);
    void onConnectedChanged();
};

#endif	/* MAINWINDOW_H */