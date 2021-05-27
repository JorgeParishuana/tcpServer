#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPServer; }
QT_END_NAMESPACE

class TCPServer : public QMainWindow
{
    Q_OBJECT

public:
    TCPServer(QWidget *parent = nullptr);
    ~TCPServer();

private:
    Ui::TCPServer *ui;
    //Socket server
    QTcpServer *qTcpServer = nullptr;
    //MessageArray
    QVector<QString> randomMessages;

    //functions
    void initServer();

private slots:
    void sendRandomMessage();

};
#endif // TCPSERVER_H
