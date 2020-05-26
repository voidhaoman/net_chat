#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QVector>
#include "room.h"

class RoomManager
{
private:
    RoomManager();
    static RoomManager* instance;
    QVector<Room> rooms;
public:
    static RoomManager* getInstance(){return instance;}

    QVector<Room>& getRooms(){return rooms;}
};

#endif // ROOMMANAGER_H
