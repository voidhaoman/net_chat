#include "roomdialog.h"
#include "ui_roomdialog.h"
#include "protocol.h"
#include "clientsocketmanager.h"

RooMDialog::RooMDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RooMDialog)
{
    ui->setupUi(this);
}

RooMDialog::~RooMDialog()
{
    delete ui;
}
QString RooMDialog::getName() const
{
    return name;
}

void RooMDialog::setName(const QString &value)
{
    name = value;
}
void RooMDialog::on_btEnter_clicked()
{
    //获取内容
    QString roomname = ui->leRoom->text();
    ui->leRoom->clear();

    //发送给服务器
    Protocol p;
    p.setType(Protocol::createRoom);
    p["roomname"] = roomname;
    p["username"] = name;//房主

    ClientSocketManager::getInstance()->write(p.toByteArray());
    this->hide();

}

void RooMDialog::on_pushButton_2_clicked()
{
    this->hide();
}
