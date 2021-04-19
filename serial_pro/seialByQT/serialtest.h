#ifndef SERIALTEST_H
#define SERIALTEST_H

#include <QObject>

#include "controlserial.h"
class serialTest : public QObject
{
    Q_OBJECT
public:
    explicit serialTest(QObject *parent = nullptr);

signals:

private:
    ControlSerial *controlSerial;

};

#endif // SERIALTEST_H
