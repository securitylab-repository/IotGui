#include "mainwindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    // if you want to register a c++ class in qml

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<QVector<float> >("QVector<float>");


    return a.exec();
}
