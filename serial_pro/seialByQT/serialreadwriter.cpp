#include "serialreadwriter.h"

SerialReadWriter::SerialReadWriter(QObject *parent) : QObject(parent)
{

}

void SerialReadWriter::onInit()
{
    m_serial = new QSerialPort();

}

void SerialReadWriter::onConfigSerial(const IControlSerial::sSerialParams &params)
{
    m_serialParams = params;

}

bool SerialReadWriter::onOpenSerial()
{
    m_serial->setPortName("/dev/ttyS1");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(m_serial, &QSerialPort::readyRead,this,&SerialReadWriter::onReceivedData);

    if(!m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << QObject::tr("Failed to open port %1, error: %2")
                    .arg(m_serial->errorString())
                 << endl;
        return false;
    }
    return true;
}

bool SerialReadWriter::onReOpenSerial()
{
    m_serial->setPortName("/dev/ttyS1");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if(!m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << QObject::tr("Failed to open port %1, error: %2")
                    .arg(m_serial->errorString())
                 << endl;
        return false;
    }
    return true;

}

void SerialReadWriter::onCloseSerial()
{

    if(m_serial != nullptr)
    {
        disconnect(m_serial, &QSerialPort::readyRead,this,&SerialReadWriter::onReceivedData);
        m_serial->close();
    }

}


void SerialReadWriter::onReceivedData()
{
    if(m_serial != nullptr)
    {
      qDebug()<< m_serial->readAll();

    }
}

void SerialReadWriter::onWriteData(const QByteArray &data )
{
    int result = -1;

    if(m_serial != nullptr)
    {
        qDebug() << QObject::tr(__func__);
        result = m_serial->write(data);
        emit writtenDataLengh(result);
        qDebug()<< "writtenDataLengh:" << result;

    }

}
