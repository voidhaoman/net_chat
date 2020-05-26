#include "receivevoice.h"
#include <QAudioDeviceInfo>


ReceiveVoice::ReceiveVoice(QString IP,QWidget *parent)
    :QMainWindow(parent),
      IP(IP)
{

    qDebug()<<IP;
    socketAudioRead=new QUdpSocket(this);
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


    audioOutputIODevice=audioOutput->start();
    socketAudioRead->bind(QHostAddress::AnyIPv4,10001,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(socketAudioRead,SIGNAL(readyRead()),this,SLOT(onReadyReadAudio()));

}

ReceiveVoice::~ReceiveVoice()
{

}

void ReceiveVoice::onReadyReadAudio()
{
    qDebug()<<"onReadyReadAudio";
    AudioPackage1 pack;
    memset(&pack,0,sizeof(AudioPackage1));
    socketAudioRead->readDatagram((char *)&pack,sizeof(AudioPackage1));
    audioOutputIODevice->write(pack.data,pack.dataLen);
}
QString ReceiveVoice::getIP() const
{
    return IP;
}

void ReceiveVoice::setIP(const QString &value)
{
    IP = value;
}
