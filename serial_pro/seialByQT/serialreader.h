#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>
class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);

signals:
    void receivedData(QByteArray data);

private:
    QSerialPort* m_serialReader;

public slots:
    bool onConnect(QSerialPort * serial );
    bool onDisConnect();

private slots:
    void onReceivedData();
    void onWriteData(const QByteArray &data );

};

#endif // SERIALREADER_H
