/* 
 * File:   XmlReader.h
 * Author: ckarner
 *
 * Created on October 23, 2015, 10:05 PM
 */

#ifndef XMLREADER_H
#define	XMLREADER_H

#include "DataRepository.h"
#include <QtXml>
#include "Directory.h"

class XmlReader : public QObject {
    Q_OBJECT
    
public:
    XmlReader(DataRepository* repository);
    bool read();
    void parse();
    void readContact();
    void readDirectory();
    void readImap();
    void readSmtp();
    void readMail();
    
private:
    Directory* currentDir;
    DataRepository* repository;
    QXmlStreamReader reader;
    Directory* getParentDirectoryById(int parentId);
    void associateDirectories();
    void buildHierarchicalList();
    void associateMails();
    
signals:
    void completed();
};

#endif	/* XMLREADER_H */