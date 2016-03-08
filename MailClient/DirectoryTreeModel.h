/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeModel.h
 * Author: ckarner
 *
 * Created on November 12, 2015, 10:11 AM
 */

#ifndef DIRECTORYTREEMODEL_H
#define DIRECTORYTREEMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QModelIndex>
#include "DirectoryTreeItem.h"
#include "Directory.h"

class DirectoryTreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    DirectoryTreeModel(const QList<Directory*>& list, QObject* parent = 0);
    virtual ~DirectoryTreeModel();
    
    void changeData(const QList <Directory*>& list);
    
    void passData(const QList<Directory*>& list);
    
    QVariant data(const QModelIndex& index, int role)const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    
    Directory* getData(const QModelIndex& index) const;
    
private:
    void setupModelData(const QList<Directory*>& list, DirectoryTreeItem* parent);
    DirectoryTreeItem* rootItem;
    Directory* rootDirectory;
    QList<Directory*> directoryList;
};

#endif /* DIRECTORYTREEMODEL_H */

