#include "icontrolserial.h"

IControlSerial::IControlSerial(QObject *parent) : QObject(parent)
{
     qRegisterMetaType<IControlSerial::eSerialState>();
     qRegisterMetaType<IControlSerial::sSerialParams>();
}
