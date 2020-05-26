#ifndef RECEIVEVOICE_H
#define RECEIVEVOICE_H

#include <QMainWindow>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QUdpSocket>
#include <QIODevice>
#include <QAudioDeviceInfo>
#include <QHostAddress>

struct AudioPackage1{
    char data[1024];
    qint64 dataLen;
};
class ReceiveVoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceiveVoice(QString IP,QWidget *parent = nullptr);
    ~ReceiveVoice();

    //进行本地的麦克风、收音机等设备的  音频采集
    QAudioInput *audioInput;
    //实现把本地的音频数据输出到音频输出设备， 音频播放
    QAudioOutput *audioOutput;

    QIODevice  * audioOutputIODevice;

    QUdpSocket * socketAudioRead;

    QHostAddress groupAddress;

    QString getIP() const;
    void setIP(const QString &value);

private slots:

    void onReadyReadAudio();

private:
    QString IP;

};

#endif // RECEIVEVOICE_H
