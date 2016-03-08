/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fibonacci.h
 * Author: ckarner
 *
 * Created on December 19, 2015, 12:26 AM
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <QString>
#include <QList>
#include <QChar>

class Fibonacci {
public:
    Fibonacci();
    QString encrypt(QString plainText) const;
    QString decrypt(QString cipherText) const;
private:
    const QList<int> fibonacci = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    const QList<QChar> possibleCharacters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '='};
};

#endif /* FIBONACCI_H */

