/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MailTableModel.h
 * Author: ckarner
 *
 * Created on December 1, 2015, 2:45 PM
 */

#ifndef MAILTABLEMODEL_H
#define MAILTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include "Mail.h"

class MailTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    MailTableModel(const QList<Mail*>& list, QObject* parent);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setData(const QList<Mail*> &list);
    QList<Mail*> getData() const;
    void clear();
    
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex());
private:
    QList<Mail*> list;
};

#endif /* MAILTABLEMODEL_H */

