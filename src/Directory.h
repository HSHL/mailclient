/* 
 * File:   Directory.h
 * Author: ckarner
 *
 * Created on November 30, 2015, 9:19 AM
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>
#include <QString>
#include <QList>

class Mail;

class Directory : public QObject {
    Q_OBJECT
    
public:
    Directory(QString name, Directory* parent = 0);
    QString getName() const;
    void setName(QString name);
    void setId(int id);
    int getId() const;
    void setParentDirectory(Directory* parent);
    Directory* getParentDirectory() const;
    void setUidNext(unsigned int uidNext);
    unsigned int getUidNext() const;
    void setOldUidNext(unsigned int uidNext);
    unsigned int getOldUidNext() const;
    void setUidValidity(unsigned int uidValidity);
    unsigned int getUidValidity() const;
    QString getPath();

private:
    QString name;
    Directory *parent;
    int id;

    unsigned int uidNext;
    unsigned int oldUidNext;
    unsigned int uidValidity;
};

#endif /* DIRECTORY_H */