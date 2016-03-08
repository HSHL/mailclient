/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.cpp
 * Author: ckarner
 * 
 * Created on December 11, 2015, 10:06 PM
 */

#include "Interface.h"

#include "DataRepository.h"

Interface::Interface(DataRepository* repository) {
    imap = new Imap(repository);
    smtp = new Smtp(repository);
}

Imap* Interface::getImap() const {
    return imap;
}

Smtp* Interface::getSmtp() const {
    return smtp;
}