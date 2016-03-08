/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectoryTreeView.h
 * Author: ckarner
 *
 * Created on December 12, 2015, 3:37 PM
 */

#ifndef DIRECTORYTREEVIEW_H
#define DIRECTORYTREEVIEW_H

#include <QTreeView>
#include <QWidget>

class DirectoryTreeView : public QTreeView {
    Q_OBJECT
public:
    DirectoryTreeView(QWidget *parent = 0);
    DirectoryTreeView(const DirectoryTreeView& orig);
    virtual ~DirectoryTreeView();
private:
    
};

#endif /* DIRECTORYTREEVIEW_H */

