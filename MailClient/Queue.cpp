/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Queue.cpp
 * Author: ckarner
 * 
 * Created on November 29, 2015, 12:40 AM
 */

#include "Queue.h"
#include <QDebug>

Queue::Queue(unsigned int interval, QObject *parent) : QObject(parent) {
    this->interval = interval;
    if (this->interval != 0) {
        connect(&timer, SIGNAL(timeout()), this, SLOT(keepAlive()));
        timer.start(this->interval);
    }
    
    _connected = false;
    _pipeReady = true;
}

/*
 * Add new command (including the directory it affects) to the queue and execute it if possible
 */

void Queue::push(QString cmd, Directory *dir) {
    QPair<QString, Directory*> pair(cmd, dir);
    commandList.append(pair);
    if (_pipeReady == true) {
        _pipeReady = false;
        pair = commandList.takeFirst();
        emit nextCommand(pair.first, pair.second);
        
        if (this->interval != 0) {
            timer.start();
        }
    }
    
    return;
}

/*
 * Execute next command
 */

void Queue::pipeReady() {
    _pipeReady = true;
    if (!commandList.isEmpty()) {
        _pipeReady = false;
        QPair<QString, Directory*> pair = commandList.takeFirst();
        emit nextCommand(pair.first, pair.second);
        
        if (this->interval != 0) {
            timer.start();
        }
    }
    
    return;
}

bool Queue::isEmpty() const {
    return commandList.isEmpty();
}

unsigned int Queue::getInterval() const {
    return this->interval;
}

void Queue::setInterval(unsigned int interval) {
    this->interval = interval;
    
    if (interval != 0) {
        this->timer.start(this->interval);
    }
    else {
        this->timer.stop();
    }
    
    return;
}

/*
 * Avoid connection timeout
 */

void Queue::keepAlive() {
    if (interval != 0) {
        if (_connected) {
            push("NOOP");
        }
    }
}

Queue& Queue::operator =(Queue q) {
    this->interval = q.interval;
    
    if (this->interval != 0) {
        timer.start(this->interval);
    }
    
    return *this;
}

Queue::Queue(const Queue& orig) : QObject(orig.parent()) {
    this->interval = orig.interval;
    
    if (this->interval != 0) {
        timer.start(this->interval);
    }
}

void Queue::connected() {
    this->_connected = true;
    
    return;
}

void Queue::disconnected() {
    this->_connected = false;
    
    return;
}

void Queue::clear() {
    this->commandList.clear();
}