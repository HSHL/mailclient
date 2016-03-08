/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.h
 * Author: ckarner
 *
 * Created on December 10, 2015, 9:45 PM
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings {
    
public:
    Settings();
    
    void setImapLogin(QString imapLogin);
    QString getImapLogin() const;
    
    void setImapPassword(QString imapPassword);
    QString getImapPassword() const;
    
    void setImapHost(QString imapHost);
    QString getImapHost() const;
    
    void setImapPort(unsigned int imapPort);
    unsigned int getImapPort() const;
    
    void setImapTimeout(unsigned int imapTimeout);
    unsigned int getImapTimeout() const;
    
    void setSmtpLogin(QString smtpLogin);
    QString getSmtpLogin() const;
    
    void setSmtpPassword(QString smtpPassword);
    QString getSmtpPassword() const;
    
    void setSmtpHost(QString smtpHost);
    QString getSmtpHost() const;
    
    void setSmtpPort(unsigned int smtpPort);
    unsigned int getSmtpPort() const;
    
    void setTls(bool value);
    bool useTls() const;
private:
    QString imapLogin;
    QString imapPassword;
    QString imapHost;
    unsigned int imapPort;
    unsigned int imapTimeout;
    
    QString smtpLogin;
    QString smtpPassword;
    QString smtpHost;
    unsigned int smtpPort;
    bool smtpTls;
};

#endif /* SETTINGS_H */

