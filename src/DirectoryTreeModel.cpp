/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeModel.cpp
 * Author: ckarner
 * 
 * Created on November 12, 2015, 10:11 AM
 */

#include "DirectoryTreeModel.h"
#include "DirectoryTreeItem.h"
#include "AddressBookWindow.h"
#include <QList>
#include <QVariant>
#include <QModelIndex>
#include "Directory.h"
#include <QIcon>

DirectoryTreeModel::DirectoryTreeModel(const QList<Directory*>& list, QObject* parent) : QAbstractItemModel(parent) {
    rootDirectory = new Directory("Directories");
    rootItem = new DirectoryTreeItem(rootDirectory);
    directoryList = list;
    setupModelData(directoryList, rootItem);
    
    passData(list);
}

void DirectoryTreeModel::changeData(const QList<Directory*>& list) {
    delete rootDirectory;
    delete rootItem;
    
    passData(list);
}

void DirectoryTreeModel::passData(const QList<Directory*>& list) {
    rootDirectory = new Directory("Directories");
    rootItem = new DirectoryTreeItem(rootDirectory);
    directoryList = list;
    setupModelData(directoryList, rootItem);
}

void DirectoryTreeModel::setupModelData(const QList<Directory*>& list, DirectoryTreeItem* parent) {
    DirectoryTreeItem* child;
    
    foreach (Directory* dir, list) {
        child = new DirectoryTreeItem(dir, parent);
                        
        parent->appendChild(child);
        
        if (dir->getSubDirectories().count() != 0) {
            setupModelData(dir->getSubDirectories(), child);
        }
    }
}

DirectoryTreeModel::~DirectoryTreeModel() {
    delete rootItem;
}

QModelIndex DirectoryTreeModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    
    DirectoryTreeItem* parentItem;
    
    if (!parent.isValid()) {
        parentItem = rootItem;
    }
    else {
        parentItem = static_cast<DirectoryTreeItem*>(parent.internalPointer());
    }
    
    DirectoryTreeItem* childItem = parentItem->child(row);
    
    if (childItem) {
        return createIndex(row, column, childItem);
    }
    else {
        return QModelIndex();
    }
}

QModelIndex DirectoryTreeModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }
    
    DirectoryTreeItem* childItem = static_cast<DirectoryTreeItem*>(index.internalPointer());
    DirectoryTreeItem* parentItem = childItem->parent();
    
    if (parentItem == rootItem) {
        return QModelIndex();
    }
    
    return createIndex(parentItem->row(), 0, parentItem);
}

int DirectoryTreeModel::rowCount(const QModelIndex& parent) const {
    DirectoryTreeItem* parentItem;
    
    if (parent.column() > 0) {
        return 0;
    }
    
    if (!parent.isValid()) {
        parentItem = rootItem;
    }
    else {
        parentItem = static_cast<DirectoryTreeItem*>(parent.internalPointer());
    }
    
    return parentItem->childCount();
}

int DirectoryTreeModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return static_cast<DirectoryTreeItem*>(parent.internalPointer())->columnCount();
    }
    else {
        return rootItem->columnCount();
    }
}

QVariant DirectoryTreeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    
    if (role == Qt::DecorationRole) {
        QIcon icon = QIcon::fromTheme("folder");
        return icon;
    }
    
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    
    DirectoryTreeItem* item = static_cast<DirectoryTreeItem*>(index.internalPointer());
    
    return item->data(index.column());
}

Qt::ItemFlags DirectoryTreeModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return 0;
    }
    
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant DirectoryTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return rootItem->data(section);
    }
    
    return QVariant();
}

Directory* DirectoryTreeModel::getData(const QModelIndex& index) const {
    DirectoryTreeItem* item = static_cast<DirectoryTreeItem*>(index.internalPointer());
    
    return item->getData(index.column());
}