#include "user.h"

User::User(QTcpSocket *socket, QString username)
    : socket(socket), username(username)
{

}

QTcpSocket *User::getSocket() const
{
    return socket;
}

void User::setSocket(QTcpSocket *value)
{
    socket = value;
}

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}
