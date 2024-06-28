#include "mainwindow.h"
#include <cstdlib> // For system()
#include <iostream>
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


