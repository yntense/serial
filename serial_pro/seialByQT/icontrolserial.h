#ifndef ICONTROLSERIAL_H
#define ICONTROLSERIAL_H

#include <QObject>
#include <QtSerialPort>
class IControlSerial : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        Fail = 0,
        SUCCESS = 0

    }eSerialState;

    typedef struct
    {
        QString serialName;
        QSerialPort::BaudRate bauRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;

    }sSerialParams;

    explicit IControlSerial(QObject *parent = nullptr); //
signals:
    void returnSerialState(eSerialState serialState);
    void receivedData(QByteArray data);
    void errHandle(QSerialPort::SerialPortError error);

public slots:
    virtual void onConfigSerial(sSerialParams params) = 0;
    virtual void onWriteData(const QByteArray &data) = 0;
    virtual void onOpen() = 0;
    virtual void onClose() = 0;



};

Q_DECLARE_METATYPE(IControlSerial::eSerialState);
Q_DECLARE_METATYPE(IControlSerial::sSerialParams);
#endif // ICONTROLSERIAL_H
