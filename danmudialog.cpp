#include "danmudialog.h"
#include "ui_danmudialog.h"
#include "clientsocketmanager.h"

DanmuDialog::DanmuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DanmuDialog)
{
    ui->setupUi(this);
}

DanmuDialog::~DanmuDialog()
{
    delete ui;
}

void DanmuDialog::on_leDanmu_returnPressed()
{
    //获取内容
    QString text = ui->leDanmu->text();
    ui->leDanmu->clear();
    this->hide();

    emit danmuText(text);
}
