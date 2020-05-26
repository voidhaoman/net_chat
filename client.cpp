#include "client.h"
#include "clientsocketmanager.h"
#include <QMessageBox>

Client::Client(QObject *parent)
    : QObject(parent),
      chatWidget(new Chatwidget),
      loginWidget(new LoginWidget),
      mainWidget(new MainWidget),
      roomDialog(new RooMDialog),
      updatePswdDialog(new UpdatePswdDialog)

{
    ClientSocketManager::getInstance()->initSocket();
    const ClientSocket* socket = ClientSocketManager::getInstance()->getClientSocket();

    QObject::connect(socket, SIGNAL(registerSuccess(QString)),
                     this, SLOT(onRegisterSuccess(QString)));//注册成功

    QObject::connect(socket, SIGNAL(registerFailed(QString)),
                     this, SLOT(onRegisterFailed(QString)));//注册失败

    QObject::connect(socket, SIGNAL(loginSuccess(QString,QString)),
                     this, SLOT(onLoginSuccess(QString,QString)));

    QObject::connect(socket, SIGNAL(loginFailed(QString)),
                     this, SLOT(onLoginFailed(QString)));

    QObject::connect(socket, SIGNAL(quit()), this, SLOT(onQuit()));

    QObject::connect(socket, SIGNAL(chat(QString)), chatWidget, SLOT(onChat(QString)));

    QObject::connect(socket, SIGNAL(refreshUser(QStringList)),
                     chatWidget, SLOT(onRefreshUser(QStringList)));

    QObject::connect(socket, SIGNAL(refreshRoom(QStringList)),
                     mainWidget,SLOT(onRefreshRoom(QStringList)));//房间刷新

    QObject::connect(mainWidget, SIGNAL(createRoom()),
                     roomDialog,SLOT(show()));//创建房间

    QObject::connect(socket, SIGNAL(createRoomsucces(QString)),
                     this,SLOT(onCreateRoomSuccess(QString)));//创建房间成功后，给出提示

    QObject::connect(mainWidget, SIGNAL(enterRoom(QString)),
                     this,SLOT(onEnterRoomSuccess(QString)));//双击后，进入房间，打开聊天窗口

    QObject::connect(socket, SIGNAL(setRoomMessage(QStringList)),
                     chatWidget,SLOT(onsetRoomMessage(QStringList)));//修改聊天窗口的信息

    QObject::connect(socket, SIGNAL(quitRoom()),
                     this, SLOT(onQuitRoom()));//退出房间

    QObject::connect(socket, SIGNAL(danmu(QString)),
                     chatWidget, SLOT(SendBar(QString)));//发送弹幕

    QObject::connect(socket, SIGNAL(giftSuccess(QString)),
                     this, SLOT(onGiftSuccess(QString)));

    QObject::connect(socket, SIGNAL(giftFailed(QString)),
                     this, SLOT(onGiftFailed(QString)));

    QObject::connect(socket, SIGNAL(rechargeSucess(QString)),
                     this, SLOT(onrechargeSucess(QString)));

    QObject::connect(socket, SIGNAL(UpdateAccount(int)),
                     chatWidget, SLOT(onUpdateAccount(int)));

    QObject::connect(mainWidget, SIGNAL(createRoom()),
                     roomDialog,SLOT(show()));//修改密码


    QObject::connect(socket, SIGNAL(updatePswdSuccess(QString)),
                     this, SLOT(onupdatePswdSuccess(QString)));

    QObject::connect(socket, SIGNAL(updatePswdFailed(QString)),
                     this, SLOT(onupdatePswdFailed(QString)));

    QObject::connect(loginWidget, SIGNAL(updatePswd()),
                     updatePswdDialog, SLOT(show()));

    QObject::connect(socket, SIGNAL(setIP(QString)),
                     chatWidget, SLOT(onsetIP(QString)));

    QObject::connect(socket, SIGNAL(setgiftMoney(int)),
                     chatWidget, SLOT(onsetgiftMoney(int)));//送礼物后，修改房主的钱

}

Client::~Client()
{
    delete chatWidget;
    delete loginWidget;
    delete mainWidget;
    delete roomDialog;
    delete updatePswdDialog;
}

void Client::show()
{
    loginWidget->show();
}
void Client::onRegisterSuccess(QString message)
{
    QMessageBox::information(loginWidget, "注册信息", message);
}

void Client::onRegisterFailed(QString message)
{
    QMessageBox::warning(loginWidget, "注册信息", message);
}

void Client::onLoginSuccess(QString username, QString message)
{
    QMessageBox::information(loginWidget, "登录信息", message);
    loginWidget->hide();

    mainWidget->show();
    chatWidget->setUsername(username);
    mainWidget->setName(username);
    roomDialog->setName(username);

}

void Client::onLoginFailed(QString message)
{
    QMessageBox::warning(loginWidget, "登录信息", message);
}

void Client::onQuit()
{
    mainWidget->hide();
    loginWidget->show();
}

void Client::onCreateRoomSuccess(QString message)
{
    QMessageBox::information(roomDialog, "注册信息", message);
}

void Client::onEnterRoomSuccess(QString roomname)
{
    chatWidget->setRoomname(roomname);    
    chatWidget->show();
}

void Client::onQuitRoom()
{
    chatWidget->hide();
    mainWidget->show();
}

void Client::onGiftSuccess(QString message)
{
    QMessageBox::information(loginWidget, "送礼信息", message);
}

void Client::onGiftFailed(QString message)
{
    QMessageBox::warning(loginWidget, "送礼信息", message);

}

void Client::onrechargeSucess(QString message)
{
    QMessageBox::information(loginWidget, "充值信息", message);
}

void Client::onupdatePswdSuccess(QString message)
{
    QMessageBox::information(updatePswdDialog, "修改信息", message);
}

void Client::onupdatePswdFailed(QString message)
{
    QMessageBox::warning(updatePswdDialog, "修改信息", message);
}
