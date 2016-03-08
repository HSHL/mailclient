/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Base64.cpp
 * Author: ckarner
 * 
 * Created on December 12, 2015, 9:40 PM
 */

#include "Base64.h"
#include <QString>
#include <QByteArray>

/*
 * Used to facilitate conversion from/to Base64 anywhere in the project
 */

QString Base64::toBase64(QString str) {
    QByteArray ar;
    ar.append(str);
    return ar.toBase64();
}

QString Base64::fromBase64(QString str){
    QByteArray ar;
    ar.append(str);
    return QByteArray::fromBase64(ar);
}