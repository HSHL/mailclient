/* 
 * File:   XmlWriter.h
 * Author: ckarner
 *
 * Created on October 24, 2015, 2:49 PM
 */

#ifndef XMLWRITER_H
#define	XMLWRITER_H

#include <QString>
#include "DataRepository.h"

class XmlWriter : public QObject {
    Q_OBJECT
public:
    XmlWriter(DataRepository* repository);
    bool write();
private:
    DataRepository* repository;
    QString getDocument();
};

#endif	/* XMLWRITER_H */

