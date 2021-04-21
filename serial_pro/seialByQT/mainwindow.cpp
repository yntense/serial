#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialState(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!serialState)
    {
        IControlSerial::sSerialParams params;
        emit configSerial(params);
        emit openSerial();
        serialState = true;
    }else{
        emit closeSerial();
        serialState = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString data = "hello write";
    emit writeSerialData(data.toUtf8());
    emit updateSerialList();
}

void MainWindow::onUpdateSerialList(const QList<QSerialPortInfo> &serialInfoLists)
{

    for (const QSerialPortInfo &info : serialInfoLists) {
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                    + QObject::tr("Location: ") + info.systemLocation() + "\n"
                    + QObject::tr("Description: ") + info.description() + "\n"
                    + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                    + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
        qDebug()<< s <<endl;
    }

}
