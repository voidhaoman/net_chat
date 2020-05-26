#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "protocol.h"
#include "clientsocketmanager.h"
#include <QMovie>
#include <QMenu>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(":/picture/blue70-2.gif");
    ui->label->setMovie(movie);
    movie->start();

//      QPalette palette;
//      palette.setBrush(QPalette::Background,QBrush(QPixmap(":/picture/blue70-2.gif")));
//      setPalette(palette);
      this->setAutoFillBackground(true);



}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btnRegister_clicked()
{
      QString username = ui->leUsername->text();
      QString userpwd = ui->leUserpwd->text();
      ui->leUsername->clear();
      ui->leUserpwd->clear();

      Protocol p;
      p.setType(Protocol::regist);
      p["username"] = username;
      p["userpwd"] = userpwd;

      ClientSocketManager::getInstance()->write(p.toByteArray());
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString userpwd = ui->leUserpwd->text();

    ui->leUsername->clear();
    ui->leUserpwd->clear();

    Protocol p;
    p.setType(Protocol::login);
    p["username"] = username;
    p["userpwd"] = userpwd;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void LoginWidget::on_btnUpdate_clicked()
{
    emit updatePswd();
}
