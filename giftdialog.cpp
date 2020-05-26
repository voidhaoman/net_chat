#include "giftdialog.h"
#include "ui_giftdialog.h"
#include "clientsocketmanager.h"

GiftDialog::GiftDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiftDialog)
{
    ui->setupUi(this);
}

GiftDialog::~GiftDialog()
{
    delete ui;
}


void GiftDialog::on_pb6_clicked()
{
    //获取内容
    emit giftMoney(6);
    this->hide();
}

void GiftDialog::on_pb100_clicked()
{
    emit giftMoney(100);
    this->hide();
}

void GiftDialog::on_pb1000_clicked()
{
    emit giftMoney(1000);
    this->hide();
}
