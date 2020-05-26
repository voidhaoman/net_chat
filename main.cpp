#include <QCoreApplication>
#include "server.h"

/*
 * 1. C/S 架构发包
 * 2. 搭建C/S
 * 3. DAO SQLITE3
 * 4. 房间管理(用户管理)
 * 5. QT 事件 信号与槽 常用控件
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    Q_UNUSED(s);

    return a.exec();
}
