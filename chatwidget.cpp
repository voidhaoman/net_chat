#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "clientsocketmanager.h"
#include <QMainWindow>
#include <barrage.h>
#include <QPushButton>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QTime>
#include <QMovie>
#include "sendvoice.h"
#include "receivevoice.h"
#include <QMessageBox>

#include "receivevideo.h"
#include "sendvideo.h"


Chatwidget::Chatwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chatwidget),
    danmuDialog(new DanmuDialog()),
    giftDialog(new GiftDialog()),
    sendvideo(new SendVideo()),
    receivevideo(new ReceiveVideo())

{

    ui->setupUi(this);
    sendvoice = nullptr;
    receivevoice = nullptr;

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/picture/background.jpg")));
    setPalette(palette);
    this->setAutoFillBackground(true);


    QObject::connect(danmuDialog, SIGNAL(danmuText(QString)), this, SLOT(onDanmu(QString)));
    QObject::connect(giftDialog, SIGNAL(giftMoney(int)), this, SLOT(onGift(int)));


    //桌面透明
//        setAutoFillBackground(false);  //这个不设置的话就背景变黑
//        setWindowFlags(Qt::FramelessWindowHint);
//        setAttribute(Qt::WA_TranslucentBackground,true);
//    按钮和编辑框的通过setGeometry(int,int,int,int)来设置大小和位置
        //获取桌面大小

}

Chatwidget::~Chatwidget()
{
    delete ui;
    delete danmuDialog;
    delete giftDialog;
    delete[] barage[500];
    delete sendvideo;
    delete receivevideo;

}

QString Chatwidget::getUsername() const
{
    return username;
}

void Chatwidget::setUsername(const QString &value)
{
    ui->lbUsername->setText("用户:"+value);
    username = value;
}

void Chatwidget::onChat(QString text)
{
    ui->tbChat->append(text);
}

void Chatwidget::on_leChat_returnPressed()
{
    //获取内容
    QString text = ui->leChat->text();
    ui->leChat->clear();

    //发送给服务器
    Protocol p;
    p.setType(Protocol::chat);
    p["roomname"] = roomname;
    p["username"] = username;
    p["chat"] = text;


    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void Chatwidget::onRefreshUser(QStringList list)
{
    ui->lwUser->clear();
    ui->lwUser->addItems(list);
}

void Chatwidget::onsetRoomMessage(QStringList list)//设置房间基本信息
{
    QString  roomname = list[0];
    QString  roomuser = list[1];
    this->setRoomuser(roomuser);
    ui->lbRoomuser->setText("房主:"+roomuser);
    ui->lbRoomname->setText("房间名:"+roomname);
}

QString Chatwidget::getRoomname() const
{
    return roomname;
}

void Chatwidget::setRoomname(const QString &value)
{
    roomname = value;
}

void Chatwidget::closeEvent(QCloseEvent *event)
{
    if(ClientSocketManager::getInstance()->isValid()){
        //网络正常
        event->ignore();
    }else{
        //网络不正常
        event->accept();
        return;
    }

    Protocol p;
    p.setType(Protocol::quitRoom);
    p["username"] = username;
    p["roomname"] = roomname;

    ui->tbChat->clear();

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void Chatwidget::on_pbGift_clicked()
{
    giftDialog->show();
}

void Chatwidget::on_pbDanmu_clicked()
{
    danmuDialog->show();
}

void Chatwidget::onDanmu(QString text)//弹幕发送给服务器
{

    //发送给服务器
    Protocol p;
    p.setType(Protocol::danmu);
    p["roomname"] = roomname;
    p["username"] = username;
    p["danmu"] = text;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void Chatwidget::SendBar(QString text)
{
     barage[i]=new Barrage(text,ui->tbChat);
     barage[i]->show();
     i++;
}
void Chatwidget::onGift(int giftMoney)
{
    if(roomname =="大厅"){
            QMessageBox::warning(this, "送礼失败", "不能给大厅送礼物");
    }else{
    //发送给服务器
    Protocol p;
    p.setType(Protocol::gift);
    p["roomname"] = roomname;
    p["username"] = username;
    p["giftMoney"] = giftMoney;

    ClientSocketManager::getInstance()->write(p.toByteArray());

    //发送给服务器
    Protocol p1;
    p1.setType(Protocol::giftDanmu);
    p1["roomname"] = roomname;
    p1["username"] = username;
    p1["giftMoney"] = giftMoney;

    ClientSocketManager::getInstance()->write(p1.toByteArray());
    }

}

void Chatwidget::on_pbrecharge_clicked()
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("充值:"),
            tr("请输入充值金额:"), 0, 0, 100000, 1, &ok);
   if (ok){

       //发送给服务器
       Protocol p;
       p.setType(Protocol::recharge);
       p["username"] = username;
       p["rechargeMoney"] = i;
       ClientSocketManager::getInstance()->write(p.toByteArray());

   }else{}
}

void Chatwidget::onUpdateAccount(int account)
{
    QString text = QString::number(account);
    ui->lbAccount->setText("账户余额:"+text);
    this->setAccount(account);
}

int Chatwidget::getAccount() const
{
    return account;
}

void Chatwidget::setAccount(int value)
{
    account = value;
}

QString Chatwidget::getIP() const
{
    return IP;
}

void Chatwidget::setIP(const QString &value)
{
    IP = value;
}
void Chatwidget::onsetIP(QString IP)
{

    this->setIP(IP);
}

void Chatwidget::onsetgiftMoney(int giftMoney)
{
    if(username == roomuser){
        account = account + giftMoney;
        QString text = QString::number(account);
        ui->lbAccount->setText("账户余额:"+text);
    }else{}
}

QString Chatwidget::getRoomuser() const
{
    return roomuser;
}

void Chatwidget::setRoomuser(const QString &value)
{
    roomuser = value;
}
void Chatwidget::on_pbVoice_clicked()
{

    if(flag == true){
        if(this->username == this->roomuser){
            sendvoice  = new SendVoice(IP,nullptr);
            flag = false;
        }else{
            receivevoice = new ReceiveVoice(IP,nullptr);
            flag = false;
        }
    }else{
        if(sendvoice != nullptr){
            delete sendvoice;
            sendvoice = nullptr;
            flag = true;

        }else if(receivevoice != nullptr){
            delete receivevoice;
            receivevoice = nullptr;
            flag = true;
        }
    }
}


void Chatwidget::on_pbVideo_clicked()
{
    if(username == roomuser){
        sendvideo->show();
    }else{
        receivevideo->show();
    }
}
