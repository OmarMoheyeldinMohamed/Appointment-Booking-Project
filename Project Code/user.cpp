#include "user.h"

User::User()
{

}

User::User(QString Username, QString Password)
{
    username = Username;
    password = Password;
}

QString User::getUsername()
{
    return username;
}

QString User::getPassword()
{
    return password;
}
