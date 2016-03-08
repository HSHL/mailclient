/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.cpp
 * Author: ckarner
 * 
 * Created on December 10, 2015, 9:45 PM
 */

#include "Settings.h"

Settings::Settings() {
    this->imapLogin = "";
    this->imapPassword = "";
    this->imapHost = "";
    this->imapPort = 0;
    this->imapTimeout = 0;
    
    this->smtpLogin = "";
    this->smtpPassword = "";
    this->smtpHost = "";
    this->smtpPort = 0;
    this->smtpTls = false;
}

void Settings::setImapLogin(QString imapLogin) {
    this->imapLogin = imapLogin;
    
    return;
}

QString Settings::getImapLogin() const {
    return this->imapLogin;
}

void Settings::setImapPassword(QString imapPassword) {
    this->imapPassword = imapPassword;
    
    return;
}

QString Settings::getImapPassword() const {
    return this->imapPassword;
}

void Settings::setImapHost(QString imapHost) {
    this->imapHost = imapHost;
    
    return;
}

QString Settings::getImapHost() const {
    return this->imapHost;
}

void Settings::setImapPort(unsigned int imapPort) {
    this->imapPort = imapPort;
    
    return;
}

unsigned int Settings::getImapPort() const {
    return this->imapPort;
}

void Settings::setImapTimeout(unsigned int imapTimeout) {
    this->imapTimeout = imapTimeout;
    
    return;
}

unsigned int Settings::getImapTimeout() const {
    return this->imapTimeout;
}

void Settings::setSmtpLogin(QString smtpLogin) {
    this->smtpLogin = smtpLogin;
    
    return;
}

QString Settings::getSmtpLogin() const {
    return this->smtpLogin;
}

void Settings::setSmtpPassword(QString smtpPassword) {
    this->smtpPassword = smtpPassword;
    
    return;
}

QString Settings::getSmtpPassword() const {
    return this->smtpPassword;
}

void Settings::setSmtpHost(QString smtpHost) {
    this->smtpHost = smtpHost;
    
    return;
}

QString Settings::getSmtpHost() const {
    return this->smtpHost;
}

void Settings::setSmtpPort(unsigned int smtpPort) {
    this->smtpPort = smtpPort;
    
    return;
}

unsigned int Settings::getSmtpPort() const {
    return this->smtpPort;
}

void Settings::setTls(bool value) {
    smtpTls = value;
    
    return;
}

bool Settings::useTls() const {
    return smtpTls;
}