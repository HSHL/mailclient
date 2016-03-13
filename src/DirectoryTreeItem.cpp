/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeItem.cpp
 * Author: ckarner
 * 
 * Created on November 12, 2015, 11:53 AM
 */

#include "DirectoryTreeItem.h"
#include "AddressBookWindow.h"
#include <QList>
#include <QVariant>
#include "Directory.h"

DirectoryTreeItem::DirectoryTreeItem(Directory* directory, DirectoryTreeItem* parent) {
    parentItem = parent;
    itemData = directory;
}

DirectoryTreeItem::~DirectoryTreeItem() {
    qDeleteAll(childItems);
}

void DirectoryTreeItem::appendChild(DirectoryTreeItem* child) {
    childItems.append(child);
}

DirectoryTreeItem* DirectoryTreeItem::child(int row) {
    return childItems.value(row);
}

int DirectoryTreeItem::childCount() const {
    return childItems.count();
}

int DirectoryTreeItem::row() const {
    if (parentItem) {
        return parentItem->childItems.indexOf(const_cast<DirectoryTreeItem*>(this));
    }
    
    return 0;    
}

int DirectoryTreeItem::columnCount() const {
    return 1;
}

QVariant DirectoryTreeItem::data(int column) const {
    return itemData->getName();
}

DirectoryTreeItem* DirectoryTreeItem::parent() {
    return parentItem;
}

Directory* DirectoryTreeItem::getData(int column) const {
    return this->itemData;
}