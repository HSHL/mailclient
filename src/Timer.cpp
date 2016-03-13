/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Timer.cpp
 * Author: ckarner
 * 
 * Created on December 6, 2015, 11:43 PM
 */

#include "Timer.h"
#include <QWidget>
#include <QDebug>

Timer::Timer(int interval, QObject *parent) : QTimer(parent) {
    this->setInterval(interval);
}

Timer::Timer(const Timer& orig) : QTimer(orig.parent()) {
    this->setInterval(orig.interval());
}

Timer& Timer::operator =(Timer t) {
    this->setInterval(t.interval());
    
    return *this;
}

void Timer::reset() {
    this->start(this->interval());
}