#include "mainwindow.h"

#include <QApplication>

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
    QObject::connect(&w,&MainWindow::updateSerialList,&controlSerial,&ControlSerial::onGetSerialList);
    QObject::connect(&controlSerial,&ControlSerial::updateSerialList,&w,&MainWindow::onUpdateSerialList);
    QObject::connect(&controlSerial,&ControlSerial::updateSerialState,&w,&MainWindow::on_listen_serial_state);

    controlSerialThread.start();
    emit w.updateSerialList();
    return a.exec();
}
