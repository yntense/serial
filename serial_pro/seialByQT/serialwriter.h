#ifndef SERIALWRITER_H
#define SERIALWRITER_H

#include <QObject>
#include <QSerialPort>
class SerialWriter : public QObject
{
    Q_OBJECT
public:
    explicit SerialWriter(QObject *parent = nullptr);

signals:
    void writtenDataLengh(int lengh);

private:
    QSerialPort* m_serialWriter = nullptr;
    int count;

public slots:
    bool onConnect(QSerialPort * serial );
    bool onDisConnect();
    void onWriteData(const QByteArray &data );

};

#endif // SERIALWRITER_H
