/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeModel.cpp
 * Author: ckarner
 * 
 * Created on November 11, 2015, 1:11 PM
 */

#include "DirectoryTreeModel.h"
#include <QList>
#include "Directory.h"
#include <QStandardItem>
#include <QDebug>
#include "DirectoryTreeNode.h"

DirectoryTreeModel::DirectoryTreeModel(const QList<Directory*> directoryList) {
    this->setItemPrototype(new DirectoryTreeNode());
    rootNode = (DirectoryTreeNode*)this->invisibleRootItem();

    this->directoryList = directoryList;
    
//    foreach (Directory* dir, directoryList) {
//        while(dir->getSubdirectories().count() != 0) {
//            QStandardItem *dirItem = new QStandardItem(dir->getName());
//            rootNode->appendRow(dirItem);
//        }
//    }
    
    buildTree(rootNode, directoryList);
}

void DirectoryTreeModel::buildTree(DirectoryTreeNode *root, const QList<Directory*> directoryList) {
    DirectoryTreeNode *dirItem;
    
    foreach (Directory* dir, directoryList) {
        dirItem = new DirectoryTreeNode(dir);
                        
        root->appendRow(dirItem);
           
        if (dir->getSubdirectories().count() != 0) {
            buildTree(dirItem, dir->getSubdirectories());
        }
    }
    
    //delete dirItem;
    //delete subDirItem;
}