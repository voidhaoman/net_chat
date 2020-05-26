#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include "danmudialog.h"
#include "giftdialog.h"
#include <barrage.h>
#include <QLineEdit>
#include "sendvoice.h"
#include "receivevoice.h"
#include "sendvideo.h"
#include "receivevideo.h"

namespace Ui {
class Chatwidget;
}

class Chatwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Chatwidget(QWidget *parent = nullptr);
    ~Chatwidget();

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getRoomname() const;
    void setRoomname(const QString &value);

    int getAccount() const;
    void setAccount(int value);

    QString getIP() const;
    void setIP(const QString &value);

    QString getRoomuser() const;
    void setRoomuser(const QString &value);

public slots:
    void onChat(QString text);
    void SendBar(QString);//发射弹幕的槽

private slots:
    void on_leChat_returnPressed();
    void onRefreshUser(QStringList list);

    void onsetRoomMessage(QStringList list);

    void on_pbDanmu_clicked();

    void on_pbGift_clicked();

    void onDanmu(QString);
    void onGift(int);

    void on_pbrecharge_clicked();

    void onUpdateAccount(int);

    void on_pbVoice_clicked();

    void onsetIP(QString);

    void onsetgiftMoney(int);

    void on_pbVideo_clicked();

private:
    Ui::Chatwidget *ui;
    DanmuDialog* danmuDialog;
    GiftDialog* giftDialog;
    QString IP;
    SendVoice* sendvoice;
    ReceiveVoice* receivevoice;

    SendVideo* sendvideo;
    ReceiveVideo* receivevideo;
    bool flag = true;



    QString username;
    QString roomname;
    QString roomuser;
    int account;

    Barrage *barage[500];
    int barnum;//弹幕数量
    int i=0;

protected:
    virtual void closeEvent(QCloseEvent* event);

};

#endif // CHATWIDGET_H
