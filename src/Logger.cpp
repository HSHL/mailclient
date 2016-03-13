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

QString Logger::timestampAsString() {
    return QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Logger::logToFile(QString fileName, QString msg) {
    QFile file(fileName);
    file.open(QFile::Append);
    QTextStream stream(&file);
    stream << timestampAsString() << ": " << msg << "\r\n";
    file.close();
}

void Logger::debug(QString message) {
    logToFile("mailClient.log", "DEBUG: " + message);
}