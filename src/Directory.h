/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Directory.h
 * Author: ckarner
 *
 * Created on November 30, 2015, 9:19 AM
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>
#include <QList>

class Mail;

class Directory : public QObject {
    Q_OBJECT
public:
    Directory();
    Directory(QString name, Directory* parent = 0);
    virtual ~Directory();
    QString getName() const;
    void setName(QString name);
    void setId(int id);
    int getId() const;
    
    void seParentId(int parentId);
    int getParentId() const;
    
    void setParentDirectory(Directory* parent);
    Directory* getParentDirectory() const;
    
    void setParentId(int parentId);
    
    void addSubDirectory(Directory* dir);
    void removeSubDirectory(Directory* dir);
    
    QList<Directory*> getSubDirectories() const;
    
    bool hasChildren() const;
    
    void setUidNext(unsigned int uidNext);
    unsigned int getUidNext() const;
    
    void setOldUidNext(unsigned int uidNext);
    unsigned int getOldUidNext() const;
    
    void setUidValidity(unsigned int uidValidity);
    unsigned int getUidValidity() const;
    
    void addMail(Mail *mail);
    void removeMail(Mail *mail);
    
    void clearMail();
    void setMailList(const QList<Mail*> mailList);
    QList<Mail*> getMailList() const;
    
private:
    QString name;
    QList<Directory*> directoryList;
    QList<Mail*> mailList;
    Directory *parent;
    int id;
    int parentId;
    
    unsigned int uidNext;
    unsigned int oldUidNext;
    unsigned int uidValidity;
};

#endif /* DIRECTORY_H */

