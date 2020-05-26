#include "sqluser.h"

SqlUser::SqlUser(const QString &username, const QString &userpwd, bool online)
    : username(username),
      userpwd(userpwd),
      online(online)
{

}

QString SqlUser::getUsername() const
{
    return username;
}

QString SqlUser::getUserpwd() const
{
    return userpwd;
}

void SqlUser::setUserpwd(const QString &value)
{
    userpwd = value;
}

bool SqlUser::getOnline() const
{
    return online;
}

void SqlUser::setOnline(bool value)
{
    online = value;
}
