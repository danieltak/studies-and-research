#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <QDebug>

void syncTest()
{
    qInfo() << "Testin'" << QThread::currentThread();
}

void syncThread()
{
    qInfo() << "Starting:" << QThread::currentThread();
    QThread::currentThread()->setObjectName("Main Thread");
    syncTest();
    qInfo() << "Finished:" << QThread::currentThread();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Synchronous example
    syncThread();

//    MainWindow w;
//    w.show();
    return a.exec();
}
