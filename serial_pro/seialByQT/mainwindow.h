#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "icontrolserial.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool serialState;
signals:
    void openSerial();
    void closeSerial();
    void configSerial(IControlSerial::sSerialParams params);
    void writeSerialData(const QByteArray &data);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
