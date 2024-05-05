/*! VUT FIT ICP
 * @file main.cpp
 * @brief Project main file  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "mainwindow.h"
#include <QApplication>

/**
 * Start point of the application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}
