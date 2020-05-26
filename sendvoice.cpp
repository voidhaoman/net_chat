#include "sendvoice.h"
#include <QAudioDeviceInfo>


SendVoice::SendVoice(QString IP,QWidget *parent)
    :QMainWindow(parent),
      IP(IP)
{

    qDebug()<<IP;
    socketWrite = new QUdpSocket(this);
    groupAddress.setAddress(IP);

    QAudioFormat format;
    format.setSampleRate(8000);   //采样率
    format.setChannelCount(1);    //信道数
    format.setSampleSize(16);     //样本大小
    format.setCodec("audio/pcm");  //编码方式
    format.setByteOrder(QAudioFormat::LittleEndian);   //字节序
    format.setSampleType(QAudioFormat::SignedInt);     //采样类型
    audioInput=new QAudioInput(QAudioDeviceInfo::defaultInputDevice(),format);
    audioOutput=new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(),format);

    audioInputIODevice=audioInput->start();
    connect(audioInputIODevice,SIGNAL(readyRead()),
            this,SLOT(captureDaaFromDevice()));

}

SendVoice::~SendVoice()
{

}



void SendVoice::captureDaaFromDevice()
{
    AudioPackage pack;
    memset(&pack,0,sizeof(AudioPackage));
    pack.dataLen=audioInputIODevice->read(pack.data,1024);
    qDebug()<<socketWrite->writeDatagram((char *)&pack,
                               sizeof (AudioPackage),
                               QHostAddress::Broadcast,
                               10001);
//    audioOutputIODevice->write(pack.data,pack.dataLen);
}
QString SendVoice::getIP() const
{
    return IP;
}

void SendVoice::setIP(const QString &value)
{
    IP = value;
}
