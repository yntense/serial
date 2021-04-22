#include "controlserial.h"

#include <QTime>

ControlSerial::ControlSerial(QObject *parent):IControlSerial(parent)
{

  qRegisterMetaType<QList<QSerialPortInfo>>();
  m_serialReadWriter = new SerialReadWriter();
  m_serialReadWriter->moveToThread(&serialReadWriterThread);
  connect(&serialReadWriterThread, &QThread::finished, m_serialReadWriter, &QObject::deleteLater);
  serialReadWriterThread.start();
  connect(m_serialReadWriter,&SerialReadWriter::updateSerialState,this,&ControlSerial::updateSerialState);
  QTimer::singleShot(0,m_serialReadWriter,&SerialReadWriter::onInit);
}

ControlSerial::~ControlSerial() {
    serialReadWriterThread.quit();
    serialReadWriterThread.wait();
}

void ControlSerial::onConfigSerial(sSerialParams params)
{
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

}

void ControlSerial::onClose()
{
    QMetaObject::invokeMethod(m_serialReadWriter, "onCloseSerial", Qt::QueuedConnection
                              );


}

void ControlSerial::onGetSerialList()
{
   const auto infos = QSerialPortInfo::availablePorts();
   emit updateSerialList(infos);

}
