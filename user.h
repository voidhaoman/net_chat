#ifndef USER_H
#define USER_H

#include <QString>
#include <QTcpSocket>

class User
{
public:
    User(QTcpSocket* socket = nullptr, QString username = "");

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);

    QString getUsername() const;
    void setUsername(const QString &value);

private:
    QTcpSocket* socket;
    QString username;
};

#endif // USER_H
