#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

#include "protocol.h"

/*
 * 通信套接字管理类
*/

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket, QObject *parent = nullptr);


signals:

private slots:
    void onReadyRead();
    void onDisconnected();

private:

    QTcpSocket* socket;
    QByteArray buffer;

    void registerHandler(const Protocol& protocol);
    void loginHandler(const Protocol& protocol);
    void quitHandler(const Protocol& protocol);
    void chatHandler(const Protocol& protocol);

    void refreshUserHandler(const QString& roomname);
    void refreshRoomHandler(const Protocol& protocol);

    void createRoomHandler(const Protocol& protocol);
    void enterRoomHandler(const Protocol& protocol);

    void quitRoomHandler(const Protocol& protocol);//退出房间

    void danmuHandler(const Protocol& protocol);

    void giftHandler(const Protocol& protocol);
    void accountRechargeHandler(const Protocol& protocol);

    void giftDanmuHandler(const Protocol& protocol);
    void refreshAccountHandler(const QString &username);

    void updatePswdHandler(const Protocol& protocol);


};

#endif // CLIENTSOCKET_H
