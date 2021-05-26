#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>

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
};
#endif // TCPSERVER_H
