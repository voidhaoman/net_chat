#include "receivevideo.h"
#include "ui_receivevideo.h"

ReceiveVideo::ReceiveVideo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReceiveVideo),
    receiver(new QUdpSocket(this)),
    groupAddress(new QHostAddress)
{
    ui->setupUi(this);

    //允许其他服务绑定到同一地址和端口。
//    receiver->bind(QHostAddress::AnyIPv4,8888,QUdpSocket::ShareAddress);
//    receiver->joinMulticastGroup(QHostAddress("224.0.0.88"));
//    groupAddress->setAddress("224.0.0.88");
//    receiver->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
//    receiver->joinMulticastGroup(*groupAddress);
//    groupAddress->setAddress("224.0.0.88");
    /*设置回环许可*/
    /*将本机加入广播组*/

    QObject::connect(receiver,SIGNAL(readyRead()),
                     this,SLOT(onReadyRead()));
}

ReceiveVideo::~ReceiveVideo()
{
    delete ui;
}

void ReceiveVideo::onReadyRead()
{
    qDebug()<<"onRead";
    static QByteArray *imageBtes=new QByteArray(228800,0);
    static QDataStream *dataStream=new QDataStream(imageBtes,QIODevice::ReadWrite);

    while(receiver->hasPendingDatagrams()){
        ImagePackage1 pack;
        memset(&pack,0,sizeof(ImagePackage1));
        receiver->readDatagram((char *)&pack,sizeof(ImagePackage1));
        if(true==pack.isLastPack){
            qDebug()<<"packTaken:"<<pack.packTaken;
            dataStream->writeRawData(pack.data,pack.packTaken);
            QImage image=QImage((uchar *)imageBtes->data(),
                                pack.width,
                                pack.height,
                                pack.bytesPerline,
                                QImage::Format_RGB32);
            QPixmap map=QPixmap::fromImage(image);
            map=map.scaled(ui->label->size());
            ui->label->setPixmap(map);//显示图片
            dataStream->device()->seek(0);
        }else{
            dataStream->writeRawData(pack.data,pack.packTaken);
        }
    }
}

QUdpSocket *ReceiveVideo::getReceiver() const
{
    return receiver;
}

void ReceiveVideo::setReceiver(QUdpSocket *value)
{
    receiver = value;
}

void ReceiveVideo::on_pbOpen_clicked()
{

        qDebug()<< getReceiver()->bind(QHostAddress::AnyIPv4,9999,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
        getReceiver()->joinMulticastGroup(QHostAddress("239.88.88.88"));
        this->getReceiver()->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 4*1024*1024);
        this->show();
}

void ReceiveVideo::on_pbClose_clicked()
{
    this->close();
}
