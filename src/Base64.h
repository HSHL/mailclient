/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Base64.h
 * Author: ckarner
 *
 * Created on December 12, 2015, 9:40 PM
 */

#ifndef BASE64_H
#define BASE64_H

#include <QString>

class Base64 {
public:
    static QString toBase64(QString str);
    static QString fromBase64(QString str);
private:
    
};

#endif /* BASE64_H */

