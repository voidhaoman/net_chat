#include "room.h"


Room::Room()
{

}

Room::Room(QString roomname, QString ownername)
    :roomname(roomname),ownername(ownername)
{

}


QString Room::getRoomname() const
{
    return roomname;
}

void Room::setRoomname(const QString &value)
{
    roomname = value;
}

QString Room::getOwnername() const
{
    return ownername;
}

void Room::setOwnername(const QString &value)
{
    ownername = value;
}

QString Room::getIP() const
{
    return IP;
}

void Room::setIP(const QString &value)
{
    IP = value;
}
