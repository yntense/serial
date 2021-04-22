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
    m_serial->setPortName(m_serialParams.serialName);
    m_serial->setBaudRate(m_serialParams.bauRate);
    m_serial->setDataBits(m_serialParams.dataBits);
    m_serial->setStopBits(m_serialParams.stopBits);
    m_serial->setParity(m_serialParams.parity);
    m_serial->setFlowControl(m_serialParams.flowControl);
    qDebug() << m_serialParams.serialName << m_serialParams.bauRate << m_serialParams.dataBits << m_serialParams.stopBits << m_serialParams.parity << m_serialParams.flowControl;
    connect(m_serial, &QSerialPort::readyRead,this,&SerialReadWriter::onReceivedData);

    if(!m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << QObject::tr("Failed to open port %1, error: %2")
                    .arg(m_serial->errorString())
                 << endl;
        emit updateSerialState(IControlSerial::OPEN_FAIL);
        return false;
    }
    emit updateSerialState(IControlSerial::OPEN_SUCCESS);
    qDebug()<< "open seial:" << m_serialParams.serialName ;
    return true;
}

bool SerialReadWriter::onReOpenSerial()
{
    m_serial->setPortName(m_serialParams.serialName);
    m_serial->setBaudRate(m_serialParams.bauRate);
    m_serial->setDataBits(m_serialParams.dataBits);
    m_serial->setStopBits(m_serialParams.stopBits);
    m_serial->setParity(m_serialParams.parity);
    m_serial->setFlowControl(m_serialParams.flowControl);
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
        emit updateSerialState(IControlSerial::CLOSE_SUCCESS);
        qDebug()<< "close seial" ;
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
