/* 
 * File:   Mail.h
 * Author: ckarner
 *
 * Created on October 15, 2015, 11:35 AM
 */

#ifndef MAIL_H
#define	MAIL_H

#include <QDateTime>
#include "Directory.h"

class Mail {
public:
    Mail();
        
    void setSenderAddress(QString value);
    QString getSenderAddress() const;
    
    void setRecipientAddress(QString value);
    QString getRecipientAddress() const;
    
    void setTimeStamp(QDateTime value);
    QDateTime getTimeStamp() const;
    
    void setSubject(QString value);
    QString getSubject() const;
    
    void setText(QString value);
    QString getText() const;
    
    void setUid(unsigned int uid);
    unsigned int getUid() const;
    
    void setRead(bool value);
    
    void setSenderName(QString senderName);
    QString getSenderName() const;
    
    bool isRead() const;
    void readMail();
    void unreadMail();
private:
    unsigned int uid;
    QString senderName;
    QString senderAddress;
    QString recipientAddress;
    QString subject;
    QDateTime timeStamp;
    QString text;
    bool read;
};

#endif	/* MAIL_H */

