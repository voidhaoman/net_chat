#include "clientsocket.h"
#include "roommanager.h"
#include "sqldao.h"
#include <QDateTime>
#include <QJsonArray>
#include <QTimer>

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent)
    : QObject(parent),
      socket(socket)
{
    //1. 读端，信号与槽
    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    //2. 对象管理
    QObject::connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}

void ClientSocket::onReadyRead()
{
    buffer += socket->readAll();

    while(1){
        QPair<bool, Protocol> ret = Protocol::unpack(buffer);
        if(ret.first == false)  return;

        Protocol& p = ret.second;

        switch(p.getType()){
        case Protocol::updatePswd:
            this->updatePswdHandler(p);
            break;
        case Protocol::refreshAccount:
            this->refreshAccountHandler(p["username"].toString());
            break;
        case Protocol::giftDanmu:
            this->giftDanmuHandler(p);
            break;
        case Protocol::recharge:
            this->accountRechargeHandler(p);
            break;
        case Protocol::gift:
            this->giftHandler(p);
            break;
        case Protocol::danmu:
            this->danmuHandler(p);
            break;
        case Protocol::quitRoom:
            this->quitRoomHandler(p);
            break;
        case Protocol::enterRoom:
            this->enterRoomHandler(p);
            break;
        case Protocol::createRoom:
            this->createRoomHandler(p);
            break;
        case Protocol::refreshRoom:
            this->refreshRoomHandler(p);
            break;
        case Protocol::refreshUser:
            this->refreshUserHandler(p["roomname"].toString());
            break;
        case Protocol::chat:
            this->chatHandler(p);
            break;
        case Protocol::quit:
            this->quitHandler(p);
            break;
        case Protocol::login:
            this->loginHandler(p);
            break;
        case Protocol::none:
            break;
        case Protocol::regist:
            this->registerHandler(p);
            break;
        }
    }
}

void ClientSocket::onDisconnected()
{
    socket->deleteLater();
    this->deleteLater();
}

void ClientSocket::registerHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString userpwd = protocol["userpwd"].toString();

    Protocol p;
    p.setType(Protocol::regist);

    SqlDao sd;
    if(sd.insertUser(SqlUser(username, userpwd))){
        //插入成功
        p["type"] = "success";
        p["message"] = "注册成功";
    }else{
        //插入失败
        p["type"] = "failed";
        p["message"] = "注册失败, 重复注册";
    }

    socket->write(p.toByteArray());

}

void ClientSocket::loginHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString userpwd = protocol["userpwd"].toString();

    Protocol p;
    p.setType(Protocol::login);
    p["username"] = protocol["username"];
    p["type"] = "failed";

    SqlDao sd;
    SqlUser user(username, userpwd);

    do{
        if(!sd.selectUser(user.getUsername(), user)){
            //没找到此用户
            p["message"] = "无此用户, 请注册";
            break;
        }

        if(user.getOnline() == 1){
            //在线
            p["message"] = "重复登录";
            break;
        }

        if(user.getUserpwd() != protocol["userpwd"].toString()){
            //密码错误
            p["message"] = "密码错误";
            break;
        }

        p["type"] = "success";
        p["message"] = "登录成功";
        int account = sd.selectAccount(username);
        p["account"] = account;

        sd.updateUserOnline(user.getUsername(), true);

        //将此用户，插入到大厅房间中
//        RoomManager::getInstance()->getRooms()[0].
//                getUsers().append(User(socket, user.getUsername()));

        this->refreshRoomHandler(p);

//        this->refreshUserHandler("");
    }while(0);
    this->refreshAccountHandler(username);

    socket->write(p.toByteArray());
}

void ClientSocket::quitHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString roomname = protocol["roomname"].toString();
    SqlDao sd;
    sd.updateUserOnline(username, false);

    Protocol p;
    p.setType(Protocol::quit);

    socket->write(p.toByteArray());

//    //1. 从包中，找到对应房间
//    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
//    int i = 0;
//    for(i = 0; i < rooms.size(); i++){
//        if(rooms[i].getRoomname() == roomname){
//            break;
//        }
//    }
//    if(i == rooms.size())   return;
//    QVector<User>& users = RoomManager::getInstance()->getRooms()[i].getUsers();
//    QVector<User>::iterator it;
//    for(it = users.begin(); it != users.end(); ++it){
//        if(it->getUsername() == username){
//            users.erase(it);
//            break;
//        }
//    }

    //房间名，大厅是空的
//    refreshUser(roomname);
}

void ClientSocket::chatHandler(const Protocol &protocol)
{
    QString roomname = protocol["roomname"].toString();
    QString username = protocol["username"].toString();
    QString message = protocol["chat"].toString();
    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    if(i == rooms.size())   return;

    QVector<User>& users = rooms[i].getUsers();

    Protocol p;
    p.setType(Protocol::chat);
    p["chat"] = message;
    p["username"] = username;

    for(i = 0; i < users.size(); i++){
        users[i].getSocket()->write(p.toByteArray());
    }
}

void ClientSocket::refreshUserHandler(const QString &roomname)
{
    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    if(i == rooms.size())   return;

    QVector<User>& users = rooms[i].getUsers();

    Protocol p;
    p.setType(Protocol::refreshUser);

    QJsonArray array;
    for(i = 0; i < users.size(); i++){
        array.append(users[i].getUsername());
    }

    p["user"] = array;//数组
    for(i = 0; i < users.size(); i++){
        users[i].getSocket()->write(p.toByteArray());
    }
}

void ClientSocket::refreshRoomHandler(const Protocol& protocol)
{
     QString username = protocol["username"].toString();


     QVector<Room>& rooms = RoomManager::getInstance()->getRooms();//调用所有房间名

     Protocol p;
     p.setType(Protocol::refreshRoom);
     QJsonArray array;
     for(int i = 0; i < rooms.size(); i++){
         array.append(rooms[i].getRoomname());
     }

     p["room"] = array;//数组
     p["username"]= username;


     socket->write(p.toByteArray());

}

void ClientSocket::createRoomHandler(const Protocol &protocol)
{
    QString roomname = protocol["roomname"].toString();
    QString username = protocol["username"].toString();


    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    rooms.append(Room(roomname,username));
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    Protocol p;
    p.setType(Protocol::createRoom);
    p["message"] = "Succes";


    socket->write(p.toByteArray());
    this->refreshRoomHandler(p);
}

void ClientSocket::enterRoomHandler(const Protocol &protocol)
{
    QString roomname = protocol["roomname"].toString();
    QString username = protocol["username"].toString();

    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }
    QString IP = rooms[i].getIP();


    QVector<User>& users = rooms[i].getUsers();
    users.append(User(socket,username));
//    for(int i=0;i<users.size();i++){
//        qDebug()<<users[i].getUsername();
//    }

    Q_UNUSED(protocol);
    Protocol p;
    p.setType(Protocol::enterRoom);
    p["message"] = "Succes";
    p["roomname"] = roomname;
    p["roomuser"] = rooms[i].getOwnername();

    p["IP"] = rooms[i].getIP();
    this->refreshUserHandler(roomname);
    socket->write(p.toByteArray());
}

void ClientSocket::quitRoomHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString roomname = protocol["roomname"].toString();


    Protocol p;
    p.setType(Protocol::quitRoom);

    socket->write(p.toByteArray());

    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }
    if(i == rooms.size())   return;
    QVector<User>& users = RoomManager::getInstance()->getRooms()[i].getUsers();
    QVector<User>::iterator it;
    for(it = users.begin(); it != users.end(); ++it){
        if(it->getUsername() == username){
            users.erase(it);
            break;
        }
    }

    //房间名，大厅是空的
    refreshUserHandler(roomname);
}

void ClientSocket::danmuHandler(const Protocol &protocol)
{
    QString roomname = protocol["roomname"].toString();
    QString username = protocol["username"].toString();
    QString message = protocol["danmu"].toString();
    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    if(i == rooms.size())   return;

    QVector<User>& users = rooms[i].getUsers();

    Protocol p;
    p.setType(Protocol::danmu);
    p["danmu"] = message;
    p["username"] = username;

    for(i = 0; i < users.size(); i++){
        users[i].getSocket()->write(p.toByteArray());
    }
}

void ClientSocket::giftHandler(const Protocol &protocol)
{

    QString username = protocol["username"].toString();
    QString roomname = protocol["roomname"].toString();
    int giftMoney = protocol["giftMoney"].toInt();

    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    if(i == rooms.size())   return;

    QString  ownername = rooms[i].getOwnername();
    SqlDao sd;
    int useraccount = sd.selectAccount(username);
    Protocol p;
    p.setType(Protocol::gift);
    if(useraccount >= giftMoney ){
        p["type"] = "success";
        p["message"] = "送礼成功!";
        sd.updateAccount(username,useraccount-giftMoney);
        int owneraccount = sd.selectAccount(ownername);
        sd.updateAccount(ownername,owneraccount+giftMoney);

    }else{
        p["type"] = "failed";
        p["message"] = "余额不足，送礼失败!";
    }
    this->refreshAccountHandler(username);
    socket->write(p.toByteArray());
}

void ClientSocket::accountRechargeHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    int rechargeMoney = protocol["rechargeMoney"].toInt();

    SqlDao sd;
    int account = sd.selectAccount(username);
    sd.updateAccount(username,account+rechargeMoney);

    Protocol p;
    p.setType(Protocol::recharge);
    p["message"] = "充值成功!";
    this->refreshAccountHandler(username);
    socket->write(p.toByteArray());
}

void ClientSocket::giftDanmuHandler(const Protocol &protocol)
{
    QString roomname = protocol["roomname"].toString();
    QString username = protocol["username"].toString();
    int giftMoney = protocol["giftMoney"].toInt();
    //1. 从包中，找到对应房间
    QVector<Room>& rooms = RoomManager::getInstance()->getRooms();
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i].getRoomname() == roomname){
            break;
        }
    }

    if(i == rooms.size())   return;

    QVector<User>& users = rooms[i].getUsers();

    SqlDao sd;
    int useraccount = sd.selectAccount(username);
    if(useraccount >= giftMoney ){
    Protocol p;
    p.setType(Protocol::giftDanmu);

    if(giftMoney == 6){
        p["message"]="办了张卡!";
    }else if(giftMoney == 100){
        p["message"]="送了一发飞机!";
    }else if(giftMoney == 1000){
        p["message"]="送了一发火箭!";
    }
    p["username"] = username;
    p["giftMoney"] = giftMoney;

    for(i = 0; i < users.size(); i++){
        users[i].getSocket()->write(p.toByteArray());
    }
    }else{}
}

void ClientSocket::refreshAccountHandler(const QString &username)
{
    SqlDao sd;
    int account = sd.selectAccount(username);

    Protocol p;
    p.setType(Protocol::refreshAccount);
    p["account"] = account;
    socket->write(p.toByteArray());
}

void ClientSocket::updatePswdHandler(const Protocol &protocol)
{
    QString username = protocol["username"].toString();
    QString userPswd = protocol["userPswd"].toString();
    QString firstPswd = protocol["firstPswd"].toString();
    QString secondPswd = protocol["secondPswd"].toString();

    Protocol p;
    p.setType(Protocol::updatePswd);
    p["username"] = protocol["username"];
    p["type"] = "failed";

    SqlDao sd;
    SqlUser user(username, firstPswd);

    do{
        if(!sd.selectUser(user.getUsername(), user)){
            //没找到此用户
            p["message"] = "无此用户";
            break;
        }
        if(firstPswd != secondPswd){
            //密码错误
            p["message"] = "两次密码输入不一致";
            break;
        }if(user.getUserpwd() != userPswd){
            p["message"] = "原密码不对!";
            break;
        }

        p["type"] = "success";
        p["message"] = "修改成功";

        sd.updateUserPwd(username,firstPswd);

    }while(0);

    socket->write(p.toByteArray());
}
