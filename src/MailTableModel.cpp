/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MailTableModel.cpp
 * Author: ckarner
 * 
 * Created on December 1, 2015, 2:45 PM
 */

#include "MailTableModel.h"
#include <QIcon>
#include "Fibonacci.h"

MailTableModel::MailTableModel(const QList<Mail*>& list, QObject* parent) {
    setData(list);
}

int MailTableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

int MailTableModel::rowCount(const QModelIndex& parent) const {
    return list.count();
}

QVariant MailTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    
    if (index.row() >= list.count() || index.row() < 0)
        return QVariant();
    
    Mail *m = list.at(index.row());
    
    if (role == Qt::DecorationRole) {
        if (index.column() == 0) {
            return QIcon::fromTheme((m->isRead())?("mail-read"):("mail-unread"));
        }
    }
    
    if (role == Qt::DisplayRole) {
        
        if (index.column() == 1)
            return (m->getSenderName() != "")?(m->getSenderName()):(m->getSenderAddress());
        else if (index.column() == 2) {
            if (!m->getSubject().startsWith("-=fib=-")) {
                return m->getSubject();
            }
            else {
                Fibonacci fibonacci;
                return fibonacci.decrypt(m->getSubject().mid(7));
            }
        }
        else if (index.column() == 3)
            return m->getTimeStamp();
    }
    
    return QVariant();
}

QVariant MailTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("");
            case 1: return tr("From");
            case 2: return tr("Subject");
            case 3: return tr("Date");
        }
    }
    return QVariant();
}

void MailTableModel::setData(const QList<Mail*>& list) {
    this->list = list;
    layoutChanged();
}

QList<Mail*> MailTableModel::getData() const {
    return this->list;
}

bool MailTableModel::removeRows(int position, int rows, const QModelIndex& parent) {
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    
    for (int row = 0; row < rows; row++) {
        list.removeAt(position);
    }
    
    endRemoveRows();
    return true;
}

void MailTableModel::clear() {
    beginResetModel();
    
    list.clear();
    
    endResetModel();
}