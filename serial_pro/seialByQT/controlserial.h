#ifndef CONTROLSERIAL_H
#define CONTROLSERIAL_H
#include <QThread>

#include "icontrolserial.h"
#include "serialreader.h"
#include "serialwriter.h"
#include "serialreadwriter.h"

class ControlSerial : public IControlSerial
{
public:
    ControlSerial(QObject *parent = nullptr);

private:
    SerialWriter * m_serialWriter;
    QThread SerialWriteThread;
    QThread SerialReaderThread;
    SerialReader * m_serialReader;
    QThread serialReadWriterThread;
    SerialReadWriter * m_serialReadWriter;
    QSerialPort* m_serial;
    eSerialState m_serialState;
signals:


public slots:
     void onConfigSerial(sSerialParams params ) override;
     void onWriteData(const QByteArray &data) override;
     void onOpen() override;
     void onClose() override;
};

#endif // CONTROLSERIAL_H
