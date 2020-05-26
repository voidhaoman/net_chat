#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "clientsocketmanager.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/picture/background2.jpg")));
    setPalette(palette);
    this->setAutoFillBackground(true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

QString MainWidget::getName() const
{
    return name;
}

void MainWidget::setName(const QString &value)
{
    name = value;
}

void MainWidget::onRefreshRoom(QStringList list)
{
    ui->lsRoom->clear();
    ui->lsRoom->addItems(list);
}

void MainWidget::closeEvent(QCloseEvent *event)
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
    p.setType(Protocol::quit);
    p["username"] = name;
    p["roomname"] = "";


    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void MainWidget::on_pbCreate_clicked()
{
    emit createRoom();
}

void MainWidget::on_lsRoom_itemDoubleClicked(QListWidgetItem *item)//双击进入房间，给客户端
{
    //获取内容
    QString roomname = item->text();

    //发送给服务器
    Protocol p;
    p.setType(Protocol::enterRoom);
    p["roomname"] = roomname;
    p["username"] = name;

    ClientSocketManager::getInstance()->write(p.toByteArray());
    this->hide();
    emit enterRoom(roomname);
}

void MainWidget::on_pbRefresh_clicked()
{
    Protocol p;
    p.setType(Protocol::refreshRoom);
    p["username"] = name;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}
