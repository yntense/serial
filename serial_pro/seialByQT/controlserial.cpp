#include "controlserial.h"

#include <QTime>
ControlSerial::ControlSerial(QObject *parent):IControlSerial(parent)
{

  m_serialReader = new SerialReader();
  m_serialReader->moveToThread(&SerialReaderThread);
  SerialReaderThread.start();

  m_serialWriter = new SerialWriter();
  m_serialWriter->moveToThread(&SerialWriteThread);
  SerialWriteThread.start();

  m_serialReadWriter = new SerialReadWriter();
  m_serialReadWriter->moveToThread(&serialReadWriterThread);
  serialReadWriterThread.start();
  QTimer::singleShot(0,m_serialReadWriter,&SerialReadWriter::onInit);
}

void ControlSerial::onConfigSerial(sSerialParams params)
{
//    m_serial = new QSerialPort(this);
//    m_serial->setPortName("/dev/ttyS1");
//    m_serial->setBaudRate(QSerialPort::Baud115200);
//    m_serial->setDataBits(QSerialPort::Data8);
//    m_serial->setStopBits(QSerialPort::OneStop);
//    m_serial->setParity(QSerialPort::NoParity);
//    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    QMetaObject::invokeMethod(m_serialReadWriter, "onConfigSerial", Qt::BlockingQueuedConnection,
                              Q_ARG(const IControlSerial::sSerialParams &, params)
                              );

}

void ControlSerial::onWriteData(const QByteArray &data)
{

    QMetaObject::invokeMethod(m_serialReadWriter, "onWriteData", Qt::QueuedConnection,
                              Q_ARG(QByteArray, data)
                              );

}

void ControlSerial::onOpen()
{

    QMetaObject::invokeMethod(m_serialReadWriter, "onOpenSerial", Qt::QueuedConnection
                              );



//    if(!m_serial->open(QIODevice::ReadWrite))
//    {
//        qDebug() << QObject::tr("Failed to open port %1, error: %2")
//                    .arg(m_serial->errorString())
//                 << endl;
//        return ;
//    }
//    bool result = false;
//    QMetaObject::invokeMethod(m_serialWriter, "onConnect", Qt::BlockingQueuedConnection,
//                              Q_RETURN_ARG(bool, result),
//                              Q_ARG(QSerialPort *, m_serial)
//                              );
//    if(result)
//    {
//        qDebug() << "connect" ;

//    }else{
//        qDebug() << "fail" ;
//    }

//    result = false;
//    QMetaObject::invokeMethod(m_serialReader, "onConnect", Qt::BlockingQueuedConnection,
//                              Q_RETURN_ARG(bool, result),
//                              Q_ARG(QSerialPort *, m_serial)
//                              );
//    if(result)
//    {
//        qDebug() << "connect" ;

//    }else{
//        qDebug() << "fail" ;
//    }


}

void ControlSerial::onClose()
{
    QMetaObject::invokeMethod(m_serialReadWriter, "onCloseSerial", Qt::QueuedConnection
                              );
//    bool result = false;
//    QMetaObject::invokeMethod(m_serialReader, "onDisConnect", Qt::BlockingQueuedConnection,
//                              Q_RETURN_ARG(bool, result)
//                              );
//    if(result)
//    {
//        qDebug() << "DisConnect success" ;

//    }else{

//        qDebug() << "DisConnect fail" ;


//    }

//    result = false;
//    QMetaObject::invokeMethod(m_serialWriter, "onDisConnect", Qt::BlockingQueuedConnection,
//                              Q_RETURN_ARG(bool, result)
//                              );
//    if(result)
//    {
//        qDebug() << "DisConnect success" ;

//    }else{

//        qDebug() << "DisConnect fail" ;


//    }

//    m_serial->close();
//    if(m_serial != nullptr)
//    {
//        delete m_serial;
//        m_serial = nullptr;
//    }




}
