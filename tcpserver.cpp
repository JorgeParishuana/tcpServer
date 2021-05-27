#include "tcpserver.h"
#include "ui_tcpserver.h"

TCPServer::TCPServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TCPServer)
{
    ui->setupUi(this);
    initServer();
    //Random Messages
    for(int i = 0;i< 20;i++){
        randomMessages<<"Mensaje aleatorio" + QString::number(i);
    }
    connect(ui->btn_close, &QAbstractButton::clicked,this, &QWidget::close);

    //Connection
    connect(qTcpServer, &QTcpServer::newConnection,this, &TCPServer::sendRandomMessage);
}

TCPServer::~TCPServer()
{
    delete ui;
}
void TCPServer::initServer(){
    qInfo()<<"initServer";
    qTcpServer = new QTcpServer(this);
    if(!qTcpServer->listen()){
        qInfo()<<"ServerError" + qTcpServer-> errorString();
        return;
    }

    QString port = QString::number(qTcpServer->serverPort(),10);
    QString ipAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(int i = 0;i<ipAddressList.size();i++){
        if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address() ){
           ipAddress = ipAddressList.at(i).toString();
           qInfo()<<"ip:" <<ipAddress;
           break;
        }
    }
    if(ipAddressList.isEmpty()){
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    QString info = "ip: "+ipAddress+",puerto = "+ port;
    ui->lbl_info->setText(info);
}

void TCPServer::sendRandomMessage(){
    qInfo()<<"Random Message";
    QByteArray qByteArray;
    QDataStream qDataStream(&qByteArray, QIODevice::WriteOnly);
    QString randomMessage = randomMessages[QRandomGenerator::global()->bounded(randomMessages.size())];
    qDataStream<<randomMessage;
    QTcpSocket *clientConnection = qTcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    clientConnection->write(qByteArray);
    clientConnection->disconnectFromHost();
    ui->lbl_Message->setText(randomMessage);
}



