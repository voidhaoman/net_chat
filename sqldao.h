#ifndef SQLDAO_H
#define SQLDAO_H

#include "sqluser.h"

class SqlDao
{
public:
    SqlDao();

    bool insertUser(const SqlUser& user);
    void deleteUser(const QString& username);

    void updateUserPwd(const QString& username, const QString& userpwd);
    void updateUserOnline(const QString& username, bool online);

    bool selectUser(const QString& username, SqlUser& user);

    void updateAccount(const QString& username,int account);

    int selectAccount(const QString& username);
};

#endif // SQLDAO_H
