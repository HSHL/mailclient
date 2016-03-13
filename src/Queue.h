/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Queue.h
 * Author: ckarner
 *
 * Created on November 29, 2015, 12:39 AM
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QTimer>

#include "Directory.h"
#include <QPair>

class Queue : public QObject {
    Q_OBJECT
public:
    Queue(unsigned int interval = 20000, QObject *parent = 0);
    Queue(const Queue& orig);
    Queue& operator =(Queue q);
    
    void push(QString cmd, Directory* = 0);
    bool isEmpty() const;   
    void clear();
    
    unsigned int getInterval() const;
    void setInterval(unsigned int interval);
   
    void connected();
    void disconnected();
    
private:
    QList<QPair<QString, Directory*>> commandList;
    
    unsigned int interval;
    bool _connected;
    bool _pipeReady;
    QTimer timer;
    
public slots:
    void pipeReady();
    
private slots:
     void keepAlive();   
    
signals:
    void nextCommand(QString cmd, Directory* dir);
};

#endif /* QUEUE_H */

