/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeModel.h
 * Author: ckarner
 *
 * Created on November 11, 2015, 1:11 PM
 */

#ifndef DIRECTORYTREEMODEL_H
#define DIRECTORYTREEMODEL_H

#include <QStandardItemModel>
#include <QStandardItem>
#include "Directory.h"
#include <QList>
#include <QModelIndex>
#include "DirectoryTreeNode.h"

class DirectoryTreeModel : public QStandardItemModel {
    Q_OBJECT    
public:
    DirectoryTreeModel(const QList<Directory*> directoryList);
private:
    void buildTree(DirectoryTreeNode *root, const QList<Directory*> directoryList);
    DirectoryTreeNode *rootNode;
    QList<Directory*> directoryList;
};

#endif /* DIRECTORYTREEMODEL_H */

