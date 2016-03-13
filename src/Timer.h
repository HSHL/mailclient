/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Timer.h
 * Author: ckarner
 *
 * Created on December 6, 2015, 11:43 PM
 */

#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QTimer {
    Q_OBJECT
public:
    Timer(int interval = 30000, QObject *parent = 0);
    Timer(const Timer& orig);
    Timer& operator =(Timer t);
    void reset();
private:
    int timeout;
};

#endif /* TIMER_H */

