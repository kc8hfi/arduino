#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new QSerialPort(this);
    //serialPort->setPortName("COM6");
    serialPort->setPortName("/dev/ttyACM3");
    serialPort->setBaudRate(9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    if (serialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"port is open in readwrite";
    }

    //connect the label to the serial port's readyread signal
    connect(serialPort,SIGNAL(readyRead()),SLOT(incoming_data()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString sendme = ui->lineEdit->text();
    sendme.append("\n");
    serialPort->write(sendme.toLatin1().constData());
    serialPort->flush();
}
void MainWindow::incoming_data()
{
    QString d = "";
    while(serialPort->canReadLine())
    {
        d.append(serialPort->readLine());
    }
    if (d.endsWith("\n"))
    {
        d = d.simplified();
        qDebug()<<d;
        ui->label_2->setText(d);
    }
}
