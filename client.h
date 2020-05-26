#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "chatwidget.h"
#include "loginwidget.h"
#include "mainwidget.h"
#include "roomdialog.h"
#include "updatepswddialog.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    virtual ~Client();

    void show();

signals:

public slots:
    void onRegisterSuccess(QString message);
    void onRegisterFailed(QString message);
    void onLoginSuccess(QString username, QString message);
    void onLoginFailed(QString message);
    void onQuit();
    void onCreateRoomSuccess(QString message);
    void onEnterRoomSuccess(QString roomname);

    void onQuitRoom();
    void onGiftSuccess(QString);
    void onGiftFailed(QString);
    void onrechargeSucess(QString);

    void onupdatePswdSuccess(QString);
    void onupdatePswdFailed(QString);

private:
    Chatwidget* chatWidget;
    LoginWidget* loginWidget;
    MainWidget* mainWidget;
    RooMDialog* roomDialog;
    UpdatePswdDialog* updatePswdDialog;

};

#endif // CLIENT_H
