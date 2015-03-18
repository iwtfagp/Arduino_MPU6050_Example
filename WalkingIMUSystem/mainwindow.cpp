#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qwt_dial_needle.h>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openSerialPort()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(writeData()));
    ui->pushButton_2->setDisabled(true);
    ui->Dial->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_2->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_3->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
}

MainWindow::~MainWindow()
{
    closeSerialPort();
    delete ui;
}


void MainWindow::openSerialPort()
{
    QString port = "COM";
    port += QString::number(ui->spinBox->value());
    serial->setPortName(port);
    serial->setBaudRate(115200);
    if (serial->open(QIODevice::ReadWrite)) {
        ui->textBrowser->setEnabled(true);
        ui->statusBar->showMessage(tr("OK"));
        ui->pushButton_2->setEnabled(true);
        ui->pushButton->setDisabled(true);
        ui->spinBox->setDisabled(true);

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        ui->statusBar->showMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort()
{
    serial->close();
    ui->textBrowser->setEnabled(false);
    ui->statusBar->showMessage(tr("Disconnected"));
}
void MainWindow::writeData()
{

    QString string = ui->lineEdit->text();
    string += "\n";
    serial->write(string.toLocal8Bit());
    ui->lineEdit->clear();
}

void MainWindow::readData()
{
//    vector<double> dataNum;
    double a = 0;

    QByteArray data = serial->readLine();
    QString str=QString::fromUtf8(data.constData());

//    QString s_data = QString::fromAscii(data.data());

    QList<QString> lines = str.split(',');
    if(lines.size() == 3){
        cout<<lines.at(1).toDouble()<<endl;
        double dataNum = lines.at(1).toDouble();
//        dataNum /= 17000.0;
//        dataNum ++;
//        dataNum *= 180.0;


        ui->Dial->setValue(lines.at(0).toDouble()+180.0);
        ui->Dial_2->setValue(lines.at(1).toDouble()+180.0);
        ui->Dial_3->setValue(lines.at(2).toDouble()+180.0);
    }
    else
        cout<<"lines.size = "<<lines.size()<<endl;


//    a = lines.at(1).toDouble();

//    foreach( const QByteArray &field, lines)
//    {
//        ;
//    }






    ui->textBrowser->append(data);
    //    if(data.contains(","))



}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
