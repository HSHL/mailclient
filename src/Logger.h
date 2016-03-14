/* 
 * File:   Logger.h
 * Author: Alexander Stuckenhol
 *
 * Created on 13. März 2016, 21:31
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <QString>

class Logger {
private:
    static void logToFile(QString fileName, QString msg);

public:
    static void debug(QString message);
    static void debug(QString source, QString message);
    
    static void error(QString message);
    static void error(QString source, QString message);
};

#endif	/* LOGGER_H */