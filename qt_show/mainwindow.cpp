#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkInterface>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette label_palette;
    label_palette.setColor(QPalette::Background, QColor(0, 0, 0));
    ui->label_image->setAutoFillBackground(true);
    ui->label_image->setPalette(label_palette);

    //--------- Init the Udp Server ----------//
    this->udpInit();
}

MainWindow::~MainWindow()
{
    delete ui;

    udp_server->close();
}

void MainWindow::udpInit()
{
    quint16 local_port = 2333;
    udp_server = new QUdpSocket(this);
    ui->textBrowser_local_ip->setText(QNetworkInterface().allAddresses().at(2).toString());

    //int ret = udp_server->bind( local_port, QUdpSocket::ShareAddress );
    int ret = udp_server->bind( QHostAddress("192.168.8.240"), local_port );
    if( ret < 0 ){
        ui->label_status->setText("bind failed");
    }
    else {
        ui->label_status->setText("port binded");
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setText("Ready For Receiving");

    // Add a Slot
    connect(udp_server, SIGNAL(readyRead()), this, SLOT(udpServerReceiveData()));
}

void MainWindow::udpServerReceiveData()
{
    QByteArray datagram;

    while( udp_server->hasPendingDatagrams() ){
        datagram.resize( udp_server->pendingDatagramSize() );

        udp_server->readDatagram(datagram.data(), datagram.size(), &client_address, &client_port);
        ui->textBrowser_ip->setText(client_address.toString());
        ui->textBrowser_port->setText(QString::number(client_port));

        // display the image
       // QImage imageTemp = getImageFromArray(datagram);
       // ui->label_image->setPixmap(QPixmap::fromImage(imageTemp).scaled(ui->label_image->size()));
        ui->textEdit_console->setText(datagram);
    }
}

QImage MainWindow::getImageFromArray( const QByteArray &buffer )
{
    QImage image;
    image.loadFromData(buffer);

    return image;
}

