#include "serialreader.h"

#include <QDebug>
SerialReader::SerialReader(QObject *parent) : QObject(parent)
{

}
bool SerialReader::onConnect(QSerialPort * serial )
{
    bool result = false;
    if(serial != nullptr)
    {
        m_serialReader = serial;
        connect(m_serialReader, &QSerialPort::readyRead,this,&SerialReader::onReceivedData);
        //connect(m_serialReader, &QSerialPort::errorOccurred, this, &SerialReader::handleError);
        result = true;
    }
    return result;

}

bool SerialReader::onDisConnect()
{
    bool result = false;
    if(m_serialReader != nullptr)
    {
        m_serialReader->disconnect(m_serialReader, &QSerialPort::readyRead,this,&SerialReader::onReceivedData);
        m_serialReader = nullptr;
        result = true;
    }
    return result;
}

void SerialReader::onReceivedData()
{
    qDebug()<< m_serialReader->readAll();


}

void SerialReader::onWriteData(const QByteArray &data )
{
    int result = -1;

    if(m_serialReader != nullptr)
    {
        qDebug() << "hello:" << QObject::tr(__func__);
        result = m_serialReader->write(data);
//        emit writtenDataLengh(result);
        qDebug()<< "writtenDataLengh:" << result;

    }

}
