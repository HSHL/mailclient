# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = MailClient
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network xml
SOURCES += AddressBook.cpp Base64.cpp Contact.cpp ContactDialog.cpp ContactPicker.cpp ContactTableModel.cpp DataRepository.cpp Directory.cpp DirectoryTreeItem.cpp DirectoryTreeModel.cpp Fibonacci.cpp Imap.cpp Interface.cpp Mail.cpp MailBox.cpp MailTableModel.cpp MailView.cpp MainWindow.cpp Queue.cpp Settings.cpp SettingsDialog.cpp Smtp.cpp XmlReader.cpp XmlWriter.cpp main.cpp
HEADERS += AddressBook.h Base64.h Contact.h ContactDialog.h ContactPicker.h ContactTableModel.h DataRepository.h Directory.h DirectoryTreeItem.h DirectoryTreeModel.h Fibonacci.h Imap.h Interface.h Mail.h MailBox.h MailTableModel.h MailView.h MainWindow.h Queue.h Settings.h SettingsDialog.h Smtp.h XmlReader.h XmlWriter.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
