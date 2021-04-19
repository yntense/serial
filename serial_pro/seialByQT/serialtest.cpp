#include "serialtest.h"


serialTest::serialTest(QObject *parent) : QObject(parent)
{
    controlSerial = new ControlSerial();
    IControlSerial::sSerialParams params ;
    controlSerial->onConfigSerial(params);
    controlSerial->onOpen();

}
