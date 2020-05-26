#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>

class SqlManager
{
private:
    SqlManager();
    static SqlManager* instance;
    QSqlDatabase db;

public:
    static SqlManager* getInstance(){return instance;}
    void open(){db.open();}
    void close(){db.close();}
};

#endif // SQLMANAGER_H
