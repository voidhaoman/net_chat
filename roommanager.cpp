#include "roommanager.h"

RoomManager::RoomManager()
{
    rooms.append(Room("大厅"));//0号房间，没有房间名，设置为打大厅
}

RoomManager* RoomManager::instance = new RoomManager;
