# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW-Windows
TARGET = mailclient
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += src/Base64.cpp src/Contact.cpp src/ContactDialog.cpp src/ContactPicker.cpp src/ContactRepository.cpp src/ContactTableModel.cpp src/ContactsDialog.cpp src/Directory.cpp src/Fibonacci.cpp src/Imap.cpp src/Logger.cpp src/Mail.cpp src/MailBox.cpp src/MailCache.cpp src/MailTableModel.cpp src/MailView.cpp src/MainWindow.cpp src/Queue.cpp src/SettingsDialog.cpp src/Smtp.cpp src/Timer.cpp src/main.cpp
HEADERS += src/Base64.h src/Contact.h src/ContactDialog.h src/ContactPicker.h src/ContactRepository.h src/ContactTableModel.h src/ContactsDialog.h src/Directory.h src/Fibonacci.h src/Imap.h src/Logger.h src/Mail.h src/MailBox.h src/MailCache.h src/MailTableModel.h src/MailView.h src/MainWindow.h src/Queue.h src/SettingsDialog.h src/Smtp.h src/Timer.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
