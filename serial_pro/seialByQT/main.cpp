#include "mainwindow.h"

#include <QApplication>

#include "controlserial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    emit w.updateSerialList();
    return a.exec();
}
