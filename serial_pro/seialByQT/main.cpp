#include "mainwindow.h"

#include <QApplication>

#include "serialtest.h"
#include "controlserial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QThread controlSerialThread;
    ControlSerial controlSerial;
    controlSerial.moveToThread(&controlSerialThread);
    QObject::connect(&w,&MainWindow::openSerial,&controlSerial,&ControlSerial::onOpen);
    QObject::connect(&w,&MainWindow::closeSerial,&controlSerial,&ControlSerial::onClose);
    QObject::connect(&w,&MainWindow::configSerial,&controlSerial,&ControlSerial::onConfigSerial);
    QObject::connect(&w,&MainWindow::writeSerialData,&controlSerial,&ControlSerial::onWriteData);

    controlSerialThread.start();

#if 0
    serialTest serialTester ;
#endif

    return a.exec();
}
