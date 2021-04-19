#include <QDebug>

#include "serialwriter.h"


SerialWriter::SerialWriter(QObject *parent) : QObject(parent)
{

}

bool SerialWriter::onConnect(QSerialPort * serial )
{
    bool result = false;
    if(serial != nullptr)
    {
        m_serialWriter = serial;
//        connect(m_serialWriter, &QSerialPort::readyRead,this,&SerialWriter::onReceivedData);
        //connect(m_serialReader, &QSerialPort::errorOccurred, this, &SerialReader::handleError);
        result = true;
    }
    return result;

}

bool SerialWriter::onDisConnect()
{
    bool result = false;
    if(m_serialWriter != nullptr)
    {
//        m_serialReader->disconnect(m_serialReader, &QSerialPort::readyRead,this,&SerialReader::onReceivedData);
        m_serialWriter = nullptr;
        result = true;
    }
    return result;
}

void SerialWriter::onWriteData(const QByteArray &data )
{
    int result = -1;

    if(m_serialWriter != nullptr)
    {
        qDebug() << QObject::tr(__func__);
        result = m_serialWriter->write(data);
        emit writtenDataLengh(result);
        qDebug()<< "writtenDataLengh:" << result;

    }

}
