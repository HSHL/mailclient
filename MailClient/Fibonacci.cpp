/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fibonacci.cpp
 * Author: ckarner
 * 
 * Created on December 19, 2015, 12:26 AM
 */

#include "Fibonacci.h"
#include "Base64.h"

int getRandom(int max) {
    return qrand() % (max + 1);
}

QString Fibonacci::encrypt(QString plainText) const {
    QString input = Base64::toBase64(plainText);
    QString cipherText;
    
    int startPos = getRandom(10);
    int currentPos = startPos;
    
    foreach (QChar c, input) {
        int oldChar = possibleCharacters.indexOf(c);
        
        int newChar = (oldChar + (fibonacci.at(currentPos) % possibleCharacters.length())) % possibleCharacters.length();
                
        cipherText.append(possibleCharacters.at(newChar));
        
        if (currentPos < 10) {
            currentPos++;
        }
        else {
            currentPos = 0;
        }
    }
    
    if (startPos < 10) {
        cipherText.prepend(QString::number(startPos));
        cipherText.append('0');
    }
    else {
        cipherText.prepend(QString::number(startPos).at(1));
        cipherText.append(QString::number(startPos).at(0));
    }
    
    return cipherText;
}

QString Fibonacci::decrypt(QString cipherText) const {
    QString input = cipherText;
    QString decryptedText;
    
    int currentPos = 0;
    int startPos = 0;
    
    if (input.at(input.length() - 1) == 0) {
        bool ok;
        startPos = QString(input.at(0)).toInt(&ok);
    }
    else {
        bool ok;
        startPos = (QString(input.at(input.length() - 1)).toInt(&ok) * 10) + QString(input.at(0)).toInt(&ok);
    }
    
    currentPos = startPos;
    
    input = input.remove(0, 1);
    input = input.remove(input.length() - 1, 1);
    
    foreach (QChar c, input) {
        int oldChar = possibleCharacters.indexOf(c);
        int newChar = oldChar - (fibonacci.at(currentPos) % possibleCharacters.length());
        
        if (newChar < 0) {
            newChar = possibleCharacters.length() - newChar * (-1);
        } 
        
        decryptedText.append(possibleCharacters.at(newChar));
        
        if (currentPos < 10) {
            currentPos++;
        }
        else {
            currentPos = 0;
        }
    }
    
    QString plainText = Base64::fromBase64(decryptedText);
    
    return plainText;
}

Fibonacci::Fibonacci() {
    qsrand(time(NULL));
}