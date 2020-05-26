#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QVector>
#include "user.h"

class Room
{
public:
    Room();
    Room(QString roomname,QString ownername="");

    QString getRoomname() const;
    void setRoomname(const QString &value);

    QString getOwnername() const;
    void setOwnername(const QString &value);

    QVector<User>& getUsers(){return users;}
    QString getIP() const;
    void setIP(const QString &value);

private:
    QString roomname;
    QString ownername;
    QString IP = "239.88.88.88";
    QVector<User> users;
};

#endif // ROOM_H
