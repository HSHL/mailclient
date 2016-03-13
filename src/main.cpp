
/*
 * File:   main.cpp
 * Author: ckarner
 *
 * Created on October 15, 2015, 11:11 AM
 */

#include <QApplication>
#include <QDebug>
#include "MainWindow.h"
#include "DataRepository.h"
#include "XmlReader.h"
#include "Logger.h"

int main(int argc, char *argv[]) {
    Logger::debug("main: Application startet!");
    QApplication app(argc, argv);

    DataRepository repository;
    XmlReader reader(&repository);
    reader.read();
        
    MainWindow mainWindow(&repository);
    mainWindow.show();

    return app.exec();
}