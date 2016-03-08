/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeNode.cpp
 * Author: ckarner
 * 
 * Created on November 11, 2015, 9:05 PM
 */

#include "DirectoryTreeNode.h"
#include <QStandardItem>
#include "Directory.h"
#include <QVariant>

DirectoryTreeNode::DirectoryTreeNode() {
    
}

DirectoryTreeNode::DirectoryTreeNode(Directory *dir) {
    setData(dir);
}

void DirectoryTreeNode::setData(Directory* dir) {
    this->directory = dir;
    return;
}

QVariant DirectoryTreeNode::data(int role) const {
    
}

