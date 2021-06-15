#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void udpInit();

private slots:
    void on_pushButton_clicked();
    void udpServerReceiveData();
    QImage getImageFromArray( const QByteArray &buffer );

private:
    QUdpSocket *udp_server;
    QHostAddress client_address;
    quint16 client_port = 0;

    QImage image;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
