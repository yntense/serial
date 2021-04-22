#ifndef CONTROLSERIAL_H
#define CONTROLSERIAL_H
#include <QThread>

#include "icontrolserial.h"
#include "serialreadwriter.h"

class ControlSerial : public IControlSerial
{
    Q_OBJECT
public:
    ControlSerial(QObject *parent = nullptr);
    ~ControlSerial() ;
private:
    QThread serialReadWriterThread;
    SerialReadWriter * m_serialReadWriter;
    QSerialPort* m_serial;
    eSerialState m_serialState;

signals:
    void updateSerialList(const QList<QSerialPortInfo> &serialInfoLists);
    void updateSerialState(const IControlSerial::eSerialState &serialState);

public slots:
     void onConfigSerial(sSerialParams params ) override;
     void onWriteData(const QByteArray &data) override;
     void onOpen() override;
     void onClose() override;
     void onGetSerialList();
};

Q_DECLARE_METATYPE(QList<QSerialPortInfo>);
#endif // CONTROLSERIAL_H
