/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.h
 * Author: ckarner
 *
 * Created on December 11, 2015, 10:06 PM
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Imap.h"
#include "Smtp.h"

class DataRepository;

class Interface {
public:
    Interface(DataRepository* repository);
    Imap* getImap() const;
    Smtp* getSmtp() const;
private:
    Imap* imap;
    Smtp* smtp;
};

#endif /* INTERFACE_H */

