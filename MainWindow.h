/* 
 * File:   MainWindow.h
 * Author: ckarner
 *
 * Created on October 22, 2015, 11:30 AM
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "DataRepository.h"
#include "AddressBook.h"
#include "MailBox.h"
#include <QStackedWidget>
#include "MailView.h"
#include <QCloseEvent>
#include "ContactPicker.h"
#include <QCheckBox>

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(DataRepository *repository);
private:
    QMenu* fileMenu;
    QAction* sendMail;
    QAction* viewAddressBook;
    QAction* viewMailBox;
    QAction* viewMail;
    QAction* refreshMails;
    QAction* viewSettings;
    QAction* closeCurrent;
    QAction* clear;
    QAction* about;
    
    DataRepository* repository;
    AddressBook* addressBook;
    MailBox* mailBox;
    MailView* mailView;
    QStackedWidget* stackedWidget;
    
    ContactPicker* contactPicker;
    
    QCheckBox* chkShowCheckbox;
    
    void createMenus();
    void createActions();
    void buildGui();
    
    void closeEvent(QCloseEvent *event);

private slots:
    void showAddressBook(); 
    void showMailBox();
    void showMail();
    void showAbout();
    void saveData();
    void showSettings();
    void closeCurrentWidget();
    void startTransmission();
    void clearMail();
    void sendSuccess(QString response);
    void sendFailure(QString response);
    void onConnectedChanged();
    
public slots:
    void showClose(bool value);   
signals:
    void settingsChanged();
    void showTransmission(int value);
};

#endif	/* MAINWINDOW_H */

