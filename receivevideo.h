#ifndef RECEIVEVIDEO_H
#define RECEIVEVIDEO_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class ReceiveVideo;
}
typedef struct
{
    int width;
    int height;
    int bytesPerline;
    bool isLastPack;
    int packTaken;
    char data[512];
}ImagePackage1;
class ReceiveVideo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceiveVideo(QWidget *parent = nullptr);
    ~ReceiveVideo();
    QUdpSocket *getReceiver() const;
    void setReceiver(QUdpSocket *value);


private:
    Ui::ReceiveVideo *ui;
    QUdpSocket * receiver;
    QHostAddress *groupAddress;
private slots:
    void onReadyRead();
    void on_pbOpen_clicked();
    void on_pbClose_clicked();
};

#endif // RECEIVEVIDEO_H
