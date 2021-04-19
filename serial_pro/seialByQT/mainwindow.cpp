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
}
