#include "sqlmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

SqlManager::SqlManager()
    : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    db.setDatabaseName("user.db");

    open();

    //1. 准备语句
    QSqlQuery query;
    query.prepare("create table if not exists user("
                  "username text primary key,"
                  "userpwd text not null,"
                  "online integer default 0,"
                  "account integer default 0);");
    if(!query.exec()){
        qDebug()<<query.lastError();
    }

    close();
}

SqlManager* SqlManager::instance = new SqlManager;
