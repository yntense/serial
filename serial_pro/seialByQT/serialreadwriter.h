#ifndef SERIALREADWRITER_H
#define SERIALREADWRITER_H

#include <QObject>
#include <QSerialPort>
#include "icontrolserial.h"
class SerialReadWriter : public QObject
{
    Q_OBJECT
public:
    explicit SerialReadWriter(QObject *parent = nullptr);

signals:
    void receivedData(QByteArray data);
    void writtenDataLengh(int lengh);

private:
    QSerialPort* m_serial;
    IControlSerial::sSerialParams m_serialParams;

public slots:
    void onInit();
    void onConfigSerial(const IControlSerial::sSerialParams &params);
    bool onOpenSerial();
    bool onReOpenSerial();
    void onCloseSerial();


private slots:
    void onReceivedData();
    void onWriteData(const QByteArray &data );


};

#endif // SERIALREADWRITER_H
