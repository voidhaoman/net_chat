#include "barrage.h"

#include <QDebug>
Barrage::Barrage(QString text,QWidget *parent)
    : QWidget(parent),
      timer(new QTimer),
      text(text)
{
    idx++;
    label = new QLabel(text,parent);
    label->setStyleSheet("color:red");
    label->setFont(QFont("宋体",12, QFont::Bold));
    int len = qrand()%(parent->height()-2*label->height())+label->height();
    label->move(parent->width(),len);
    label->adjustSize();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(10);
}
void Barrage::onTimeout()
{
    QPoint p = label->pos();
    if(p.x()>(-label->width())){
        label->move(p.x()-1,p.y());
        label->show();
    }else{
        label->hide();
        timer->stop();
        delete  this;
    }
}
