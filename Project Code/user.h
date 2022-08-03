#ifndef USER_H
#define USER_H
#include <QString>


enum UserType {cust, work};
class User
{
public:
    User();
    User(QString, QString);
    virtual UserType gettype()=0;
    QString getUsername();
    QString getPassword();
    //void setPassword();
private:
    QString username, password;

};

#endif // USER_H
