/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeNode.h
 * Author: ckarner
 *
 * Created on November 11, 2015, 9:05 PM
 */

#ifndef DIRECTORYTREENODE_H
#define DIRECTORYTREENODE_H

#include <QStandardItem>
#include "Directory.h"
#include <QVariant>

class DirectoryTreeNode : public QStandardItem {
    Q_OBJECT
public:
    DirectoryTreeNode();
    DirectoryTreeNode(Directory* dir);
    void setData(Directory* dir);
    QVariant data(int role = Qt::UserRole + 1) const;
private:
    Directory* directory;
};

#endif /* DIRECTORYTREENODE_H */

