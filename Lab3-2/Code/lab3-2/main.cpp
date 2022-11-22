#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QTimer>
#include <QtWidgets>
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
