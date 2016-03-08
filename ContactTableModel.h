/* 
 * File:   ContactTableModel.h
 * Author: ckarner
 *
 * Created on October 16, 2015, 2:34 PM
 */

#ifndef CONTACTTABLEMODEL_H
#define	CONTACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include "Contact.h"

class ContactTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    ContactTableModel(const QList <Contact*> &list, QObject *parent, bool picker = false);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setData(const QList<Contact*> &list);
private:
    QList<Contact*> list;
    
    bool isPicker;
};

#endif	/* CONTACTTABLEMODEL_H */

