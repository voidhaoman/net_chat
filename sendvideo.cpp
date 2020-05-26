#include "sendvideo.h"
#include "ui_sendvideo.h"

#include <QCameraInfo>
#include <QDebug>
#include <QThread>
#include "videiosurface.h"

SendVideo::SendVideo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendVideo),
    socketWrite(new QUdpSocket)
{
    ui->setupUi(this);
    socketWrite->bind(QHostAddress::AnyIPv4,9999,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    socketWrite->joinMulticastGroup(QHostAddress("239.88.88.88"));

    QCameraInfo info=QCameraInfo::defaultCamera();
    camera=new QCamera(info,this);

    VideioSurface *vf=new VideioSurface(this);
    //设置取景器，捕获视频流
    camera->setViewfinder(vf);
    //将捕捉视频图片信息，发送出去
    QObject::connect(vf,SIGNAL(vedeioChanged(QVideoFrame)),this,SLOT(vedeioChangedSLot(QVideoFrame)));
}

SendVideo::~SendVideo()
{
    delete ui;
}

void SendVideo::on_pbOpen_clicked()
{
    //打开摄像头
    camera->start();
}

void SendVideo::on_pbClose_clicked()
{
    //关闭摄像头
    camera->stop();
    ui->label->clear();
}
void SendVideo::vedeioChangedSLot(QVideoFrame curFrame)
{
    static int i=0;
    i++;
    int unitBytes=512;

    //帧视频数据
    QVideoFrame frame(curFrame);
    //将视频帧的内容映射到系统（CPU可寻址）内存
    frame.map(QAbstractVideoBuffer::ReadOnly);
    //通过QVideoFrame对象构建QImage对象
    QImage image(frame.bits(),frame.width(),frame.height(),
                 QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    //将像旋转180
    QMatrix matrix;
    matrix.rotate(180);
    image=image.transformed(matrix);

    //将QImage格式转化成QPixmap格式显示图片
    QPixmap pixmap=QPixmap::fromImage(image);
    pixmap=pixmap.scaled(ui->label->size());
    ui->label->setPixmap(pixmap);

    //发送视频图片
    if(i % 4 ==0)
        return ;
    int byteCount=image.byteCount();   //图片大小
    int width=image.width();   //图片宽度
    int heigth=image.height();  //图片高度
    int bytePerLine=image.bytesPerLine();//每行字节数
//    qDebug()<<"byteCount:"<<byteCount;
//    qDebug()<<"width:"<<width;
//    qDebug()<<"heigth:"<<heigth;
//    qDebug()<<"bytePerLine:"<<bytePerLine;
    int writeBytes=0;

    while (true) {
        ImagePackage pack;
        memset(&pack,0,sizeof(ImagePackage));

        pack.width=width;
        pack.height=heigth;
        pack.bytesPerline=bytePerLine;
        if(writeBytes<byteCount){
            memcpy(pack.data,(char *)image.bits()+writeBytes,unitBytes);
//            qDebug()<<image.bits()+writeBytes;
            pack.packTaken=unitBytes;
            writeBytes +=unitBytes;
            if(writeBytes>=byteCount){
                pack.isLastPack=true;
                pack.packTaken=unitBytes-writeBytes+byteCount;
//                qDebug()<<"writeBytes:"<<writeBytes;
            }else{
                pack.isLastPack=false;
                pack.packTaken=unitBytes;
            }
            qint64 len;
        len=socketWrite->writeDatagram((char *)&pack,sizeof (ImagePackage),QHostAddress::Broadcast,9999);
        qDebug()<<"发送大小:"<<len;
        }else{
            break;
        }
    }
}
