/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeItem.h
 * Author: ckarner
 *
 * Created on November 12, 2015, 11:53 AM
 */

#ifndef DIRECTORYTREEITEM_H
#define DIRECTORYTREEITEM_H

#include <QList>
#include <QVariant>
#include "Directory.h"

class DirectoryTreeItem {
public:
    DirectoryTreeItem(Directory* directory, DirectoryTreeItem* parent = 0);
    virtual ~DirectoryTreeItem();
    
    void appendChild(DirectoryTreeItem* child);
    
    DirectoryTreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    DirectoryTreeItem *parent();
    
    Directory* getData(int column) const;
private:
    QList<DirectoryTreeItem*> childItems;
    Directory* itemData;
    DirectoryTreeItem* parentItem;
};

#endif /* DIRECTORYTREEITEM_H */

