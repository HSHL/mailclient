/* 
 * File:   Logger.cpp
 * Author: Alexander Stuckenhol
 * 
 * Created on 13. März 2016, 21:31
 */

#include "Logger.h"
#include "time.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>

void Logger::logToFile(QString fileName, QString msg) {
    QFile file(fileName);
    file.open(QFile::Append);
    QTextStream stream(&file);
    stream << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") << ": " << msg << "\r\n";
    file.close();
}

void Logger::debug(QString source, QString message) {
    logToFile("mailClient.log", QString("SOURCE: %1 DEBUG: %2").arg(source).arg(message));
}

void Logger::debug(QString message) {
    logToFile("mailClient.log", QString("DEBUG: %1").arg(message));
}

void Logger::error(QString source, QString message) {
    logToFile("mailClient.log", QString("SOURCE: %1 ERROR: %2").arg(source).arg(message));
}

void Logger::error(QString message) {
    logToFile("mailClient.log", QString("ERROR: %1").arg(message));
}