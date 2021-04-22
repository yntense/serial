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
    void updateSerialState(const IControlSerial::eSerialState &serialState);

private:
    QSerialPort* m_serial;
    IControlSerial::sSerialParams m_serialParams;
    IControlSerial::eSerialState m_serialState;

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
