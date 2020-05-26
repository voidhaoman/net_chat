#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

private slots:
    void onNewConnection();
private:
    QTcpServer* server;
};

#endif // SERVER_H
