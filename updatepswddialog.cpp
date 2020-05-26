#include "updatepswddialog.h"
#include "ui_updatepswddialog.h"
#include "protocol.h"
#include "clientsocketmanager.h"

UpdatePswdDialog::UpdatePswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdatePswdDialog)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/picture/background4.jpg")));
    setPalette(palette);
    this->setAutoFillBackground(true);
}

UpdatePswdDialog::~UpdatePswdDialog()
{
    delete ui;
}

void UpdatePswdDialog::on_pbSure_clicked()
{
    QString username = ui->leUsername->text();
    QString userPswd = ui->lePswd->text();
    QString firstPswd = ui->leFirstPwd->text();
    QString secondPswd = ui->leSecondPwd->text();

    ui->leUsername->clear();
    ui->lePswd->clear();
    ui->leFirstPwd->clear();
    ui->leSecondPwd->clear();

    Protocol p;
    p.setType(Protocol::updatePswd);
    p["username"] = username;
    p["userPswd"] = userPswd;
    p["firstPswd"] = firstPswd;
    p["secondPswd"] = secondPswd;

    ClientSocketManager::getInstance()->write(p.toByteArray());
    this->hide();
}

void UpdatePswdDialog::on_pbCancle_clicked()
{
    this->hide();
}
