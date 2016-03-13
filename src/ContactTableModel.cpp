/* 
 * File:   ContactTableModel.cpp
 * Author: ckarner
 * 
 * Created on October 16, 2015, 2:34 PM
 */

#include "ContactTableModel.h"

ContactTableModel::ContactTableModel(const QList<Contact*>& list, QObject* parent, bool picker) {
    this->isPicker = picker;
    setData(list);
}
    
int ContactTableModel::columnCount(const QModelIndex& parent) const {
    return (!isPicker)?3:2;
}
    
int ContactTableModel::rowCount(const QModelIndex& parent) const {
    return list.count();
}

QVariant ContactTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    
    if (index.row() >= list.count() || index.row() < 0)
        return QVariant();
    
    if (role == Qt::DisplayRole) {
        Contact *c = list.at(index.row());
        
        if (index.column() == 0)
            return c->firstName();
        else if (index.column() == 1)
            return c->lastName();
        else if (index.column() == 2)
            return c->mailAddress();
    }
    return QVariant();
}

QVariant ContactTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("First name");
            case 1: return tr("Last name");
            case 2: return tr("Mail address");
        }
    }
    return QVariant();
}

void ContactTableModel::setData(const QList<Contact*> &list) {
    this->list = list;
    layoutChanged();
}
