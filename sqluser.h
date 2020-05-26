#ifndef SQLUSER_H
#define SQLUSER_H

#include <QString>

class SqlUser
{
public:
    SqlUser(const QString& username = "", const QString& userpwd = "", bool online = false);

    QString getUsername() const;

    QString getUserpwd() const;
    void setUserpwd(const QString &value);

    bool getOnline() const;
    void setOnline(bool value);

private:
    const QString username;
    QString userpwd;
    bool online;
};

#endif // SQLUSER_H
