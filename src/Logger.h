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
    static QString timestampAsString();
    static void logToFile(QString fileName, QString msg);

public:
    static void debug(QString message);
};

#endif	/* LOGGER_H */

