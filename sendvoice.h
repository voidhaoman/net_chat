#ifndef SENDVOICE_H
#define SENDVOICE_H

#include <QMainWindow>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QUdpSocket>
#include <QIODevice>
#include <QAudioDeviceInfo>
#include <QHostAddress>

struct AudioPackage{
    char data[1024];
    qint64 dataLen;
};
class SendVoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendVoice(QString IP,QWidget *parent = nullptr);
    ~SendVoice();

    //进行本地的麦克风、收音机等设备的  音频采集
    QAudioInput *audioInput;
    //实现把本地的音频数据输出到音频输出设备， 音频播放
    QAudioOutput *audioOutput;

    QIODevice  * audioInputIODevice;
    QUdpSocket * socketWrite;

    QHostAddress groupAddress;

    QString getIP() const;
    void setIP(const QString &value);

private slots:

    void captureDaaFromDevice();

private:
    QString IP;

};

#endif // SENDVOICE_H
