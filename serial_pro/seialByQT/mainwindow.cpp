#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serialState(IControlSerial::CLOSE_SUCCESS)
{

    ui->setupUi(this);

    m_controlSerial = new ControlSerial();
    m_controlSerial->moveToThread(&m_controlSerialThread);
    QObject::connect(&m_controlSerialThread, &QThread::finished, m_controlSerial, &QObject::deleteLater);
    QObject::connect(this,&MainWindow::openSerial,m_controlSerial,&ControlSerial::onOpen);
    QObject::connect(this,&MainWindow::closeSerial,m_controlSerial,&ControlSerial::onClose);
    QObject::connect(this,&MainWindow::configSerial,m_controlSerial,&ControlSerial::onConfigSerial);
    QObject::connect(this,&MainWindow::writeSerialData,m_controlSerial,&ControlSerial::onWriteData);
    QObject::connect(this,&MainWindow::updateSerialList,m_controlSerial,&ControlSerial::onGetSerialList);
    QObject::connect(m_controlSerial,&ControlSerial::updateSerialList,this,&MainWindow::onUpdateSerialList);
    QObject::connect(m_controlSerial,&ControlSerial::updateSerialState,this,&MainWindow::onListenSerialState);
    m_controlSerialThread.start();
    emit updateSerialList();

    QStringList BaudRateList ,DataBitsList,stopBitsList,parityList,flowControlList;
    BaudRateList << "1200" << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "115200";
    DataBitsList << "5" << "6" << "7" << "8";
    stopBitsList << "1" << "3" << "2";
    parityList << "0" << "2" << "3" << "4" << "5";
    flowControlList << "none" << "hardware" << "software";
    ui->m_baudRate->insertItems(0,BaudRateList);
    ui->m_dataBits->insertItems(0,DataBitsList);
    ui->m_stopBits->insertItems(0,stopBitsList);
    ui->m_parity->insertItems(0,parityList);
    ui->m_flowControl->insertItems(0,flowControlList);


}

MainWindow::~MainWindow()
{
    m_controlSerialThread.quit();
    m_controlSerialThread.wait();
    delete ui;

}


void MainWindow::onUpdateSerialList(const QList<QSerialPortInfo> &serialInfoLists)
{
    QSet<QString> portSet = m_portList.toSet();
    for (const QSerialPortInfo &info : serialInfoLists) {
        if(!portSet.contains(info.portName()))
        {
            m_portList << info.portName();
            ui->port->insertItem(m_portList.size(),info.portName());
        }
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                    + QObject::tr("Location: ") + info.systemLocation() + "\n"
                    + QObject::tr("Description: ") + info.description() + "\n"
                    + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                    + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
        qDebug()<< s <<endl;
    }


}

void MainWindow::on_port_currentIndexChanged(const QString &arg1)
{
    qDebug()<< arg1 <<endl;
    m_params.serialName = arg1;
}

void MainWindow::on_port_activated(const QString &arg1)
{
     qDebug()<< arg1 <<endl;
     emit updateSerialList();
}


void MainWindow::on_open_clicked()
{

    switch (m_serialState) {
    case IControlSerial::OPEN_FAIL:
    {
        emit configSerial(m_params);
        emit openSerial();

    }
        break;
    case IControlSerial::CLOSE_SUCCESS:
    {
        emit configSerial(m_params);
        emit openSerial();

    }
        break;
    case IControlSerial::OPEN_SUCCESS:
    {
        emit closeSerial();
    }
        break;
    default:
        break;
    }
}

void MainWindow::onListenSerialState(const IControlSerial::eSerialState &serialState)
{
     m_serialState = serialState;
     switch (m_serialState) {
     case IControlSerial::OPEN_FAIL:
     {
        ui->open->setText("open");

     }
         break;
     case IControlSerial::OPEN_SUCCESS:
     {
         ui->open->setText("close");
     }
         break;
     case IControlSerial::CLOSE_SUCCESS:
     {
         ui->open->setText("open");
     }
         break;
     default:
         break;
     }
}


void MainWindow::on_m_stopBits_currentIndexChanged(const QString &stopBits)
{
    if(stopBits == "1")
    {
        m_params.stopBits = QSerialPort::OneStop;

    }else if(stopBits == "3")
    {
        m_params.stopBits = QSerialPort::OneAndHalfStop;

    }else if(stopBits == "2")
    {
        m_params.stopBits = QSerialPort::TwoStop;

    }
}



void MainWindow::on_m_parity_currentIndexChanged(const QString &parity)
{

    if(parity == "0")
    {
        m_params.parity = QSerialPort::NoParity;

    }else if(parity == "2")
    {
        m_params.parity = QSerialPort::EvenParity;

    }else if(parity == "3")
    {
        m_params.parity = QSerialPort::OddParity;

    }else if(parity == "4")
    {
        m_params.parity = QSerialPort::SpaceParity;

    }else if(parity == "5")
    {
        m_params.parity = QSerialPort::MarkParity;

    }
}

void MainWindow::on_m_flowControl_currentIndexChanged(const QString &flowContol)
{
    if(flowContol == "none")
    {
        m_params.flowControl = QSerialPort::NoFlowControl;

    }else if(flowContol == "hardware")
    {
        m_params.flowControl = QSerialPort::HardwareControl;

    }else if(flowContol == "software")
    {
        m_params.flowControl = QSerialPort::SoftwareControl;
    }
}

void MainWindow::on_m_dataBits_currentIndexChanged(const QString &dataBits)
{
    if(dataBits == "5")
    {
        m_params.dataBits = QSerialPort::Data5;

    }else if(dataBits == "6")
    {
        m_params.dataBits = QSerialPort::Data6;

    }else if(dataBits == "7")
    {
        m_params.dataBits = QSerialPort::Data7;

    }else if(dataBits == "8")
    {
        m_params.dataBits = QSerialPort::Data8;

    }
}

void MainWindow::on_m_sendbutton_clicked()
{

    emit writeSerialData(ui->m_writeArea->toPlainText().toUtf8());
}

void MainWindow::on_m_baudRate_currentIndexChanged(const QString &baudRate)
{
    if(baudRate == "1200")
    {
        m_params.bauRate = QSerialPort::Baud1200;

    }else if(baudRate == "2400")
    {
        m_params.bauRate = QSerialPort::Baud2400;

    }else if(baudRate == "4800")
    {
        m_params.bauRate = QSerialPort::Baud4800;

    }else if(baudRate == "9600")
    {
        m_params.bauRate = QSerialPort::Baud9600;

    }else if(baudRate == "19200")
    {
        m_params.bauRate = QSerialPort::Baud19200;

    }else if(baudRate == "38400")
    {
        m_params.bauRate = QSerialPort::Baud38400;

    }else if(baudRate == "57600")
    {
        m_params.bauRate = QSerialPort::Baud57600;

    }else if(baudRate == "115200")
    {
        m_params.bauRate = QSerialPort::Baud115200;

    }
    qDebug()<< m_params.bauRate <<endl;
}
