#include "server.h"
#include <QHostAddress>
#include <QTcpSocket>
#include "clientsocket.h"

/*
 * 1. 创建套接字：创建套接字对象 QTcpServer
 * 2. 绑定套接字
 * 3. 监听套接字
 * 4. 接受套接字
 * 5. 通信     : read write QTcpSocket
*/

Server::Server(QObject *parent)
    : QObject(parent)
{
    //1. 创建套接字
    server = new QTcpServer(this);

    //2. 绑定 + 监听
    server->listen(QHostAddress::Any, 10000);

    //3. 接受用信号与槽
    QObject::connect(server, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
}

void Server::onNewConnection()
{
    while(server->hasPendingConnections()){
        //接受，创建新的套接字，与客户端保持长连接
        QTcpSocket* socket = server->nextPendingConnection();
        qDebug()<<"新的连接: "<<socket->peerAddress().toString()<<" "<<socket->peerPort();
        ClientSocket* cs = new ClientSocket(socket, this);
        Q_UNUSED(cs);
    }
}
