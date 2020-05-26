#ifndef SENDVIDEO_H
#define SENDVIDEO_H

#include <QMainWindow>
#include <QCamera>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class SendVideo;
}
typedef struct
{
    int width;
    int height;
    int bytesPerline;
    bool isLastPack;
    int packTaken;
    char data[512];
}ImagePackage;
class SendVideo : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendVideo(QWidget *parent = nullptr);
    ~SendVideo();

private slots:
    void on_pbOpen_clicked();

    void on_pbClose_clicked();
    void vedeioChangedSLot(QVideoFrame);

private:
    Ui::SendVideo *ui;

    //QCamera类为系统摄像机设备提供了接口
    QCamera * camera;
    QUdpSocket *socketWrite;
    QHostAddress *groupAddress;
};

#endif // SENDVIDEO_H
