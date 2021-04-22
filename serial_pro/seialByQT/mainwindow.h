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
    IControlSerial::eSerialState m_serialState;
    QStringList m_portList;
    IControlSerial::sSerialParams m_params;
signals:
    void openSerial();
    void closeSerial();
    void configSerial(IControlSerial::sSerialParams params);
    void writeSerialData(const QByteArray &data);
    void updateSerialList();

public slots:
    void onUpdateSerialList(const QList<QSerialPortInfo> &serialInfoLists);
    void on_listen_serial_state(const IControlSerial::eSerialState &serialState);

private slots:
    void on_port_currentIndexChanged(const QString &arg1);
    void on_port_activated(const QString &arg1);
    void on_open_clicked();
    void on_m_stopBits_currentIndexChanged(const QString &arg1);
    void on_m_parity_currentIndexChanged(const QString &arg1);
    void on_m_flowControl_currentIndexChanged(const QString &arg1);
    void on_m_dataBits_currentIndexChanged(const QString &arg1);
    void on_m_sendbutton_clicked();
    void on_m_baudRate_currentIndexChanged(const QString &arg1);
};
#endif // MAINWINDOW_H
