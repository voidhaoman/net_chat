#include "sqldao.h"
#include "sqlmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

SqlDao::SqlDao()
{

}

bool SqlDao::insertUser(const SqlUser &user)
{
    bool ret = false;

    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("insert into user(username, userpwd)values(:username, :userpwd);");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":userpwd", user.getUserpwd());

    if(!(ret = query.exec())){
        qDebug()<<query.lastError().text();
    }

    SqlManager::getInstance()->close();

    return ret;
}

void SqlDao::deleteUser(const QString &username)
{
    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("delete from user where username = :username;");
    query.bindValue(":username", username);

    if(!(query.exec())){
        qDebug()<<query.lastError().text();
    }

    SqlManager::getInstance()->close();

    return;
}

void SqlDao::updateUserPwd(const QString &username, const QString &userpwd)
{
    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("update user set userpwd = :userpwd where username = :username;");
    query.bindValue(":userpwd", userpwd);
    query.bindValue(":username", username);

    if(!(query.exec())){
        qDebug()<<query.lastError().text();
    }

    SqlManager::getInstance()->close();

    return;
}

void SqlDao::updateUserOnline(const QString &username, bool online)
{
    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("update user set online = :online where username = :username;");
    query.bindValue(":online", online);
    query.bindValue(":username", username);

    if(!(query.exec())){
        qDebug()<<query.lastError().text();
    }

    SqlManager::getInstance()->close();

    return;
}

bool SqlDao::selectUser(const QString &username, SqlUser &user)
{
    bool ret = false;

    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("select * from user where username = :username;");
    query.bindValue(":username", username);

    if(!(ret = query.exec())){
        qDebug()<<query.lastError().text();
    }else{
        if((ret = query.next())){
            //有数据
            user.setUserpwd(query.value(1).toString());
            user.setOnline(query.value(2).toBool());
        }
    }

    SqlManager::getInstance()->close();

    return ret;
}
void SqlDao::updateAccount(const QString &username, int account)
{
    //1. 打开数据库
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("update user set account = :account where username = :username;");
    query.bindValue(":account", account);
    query.bindValue(":username", username);

    if(!(query.exec())){
        qDebug()<<query.lastError().text();
    }

    SqlManager::getInstance()->close();

    return;
}
int SqlDao::selectAccount(const QString &username)
{
    //1. 打开数据库
    int account=0;
    SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("select account from user where username = :username;");
    query.bindValue(":username", username);

    if(!(query.exec())){
        qDebug()<<query.lastError().text();
    }
    else{
        while(query.next()){
            account = query.value(0).toInt();
        }
    }

    SqlManager::getInstance()->close();

    return account;
}
