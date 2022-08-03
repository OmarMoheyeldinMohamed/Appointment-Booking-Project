#include "customer.h"

Customer::Customer()
{

}

Customer::Customer(QString Username, QString Password): User(Username, Password)
{

}

UserType Customer::gettype()
{
    return cust;
}

void Customer::addpending(Appointment x)
{
    readfile();
    notconfirmed.append(x);
    savetofile();
}

void Customer::readfile()
{
    QFile file(""+getUsername()+".txt");
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    confirmedappointments.clear();
    notconfirmed.clear();
    QString x;
    int count = 1, count2 = 0;
    QString num = "";
    Date d;
    d.day = 0;
    d.month = 0;
    d.year = 0;
    int time= 0;
    Appointment tempapp;
    QString prev = "";
    while (!stream.atEnd())
    {
        prev =x;
        x = stream.read(1);
        if(count == 1)
                {
                    if (x == "\n")
                    {
                        if (prev == "*")
                            continue;
                        tempapp.description = num;
                        num = "";
                        count2 = 0;
                        confirmedappointments.push_back(tempapp);
                        d.day = d.year = d.month = 0;
                    }
                    else if(x == ',')
                    {
                        if (count2==0)
                        {
                            count2++;
                            time = num.toInt();
                            tempapp.time = time;
                            num = "";
                        }
                        else if (count2 == 1)
                        {
                            count2++;
                            d.year = num.toInt();
                            tempapp.date = d;
                            num = "";

                        }
                        else if(count2 == 2)
                        {
                            count2++;
                            tempapp.address = num;
                            num = "";
                        }
                        else if(count2 == 3)
                        {
                            count2++;
                            tempapp.worker = num;
                            num = "";
                        }
                    }
                    else if(x == "*")
                    {
                        count++;

                    }
                    else if(x == "\r")
                        continue;
                    else if (x == "/")
                    {
                        if (d.day == 0)
                            d.day = num.toInt();
                        else if (d.month == 0)
                            d.month = num.toInt();
                        num = "";
                    }
                    else
                        num=num +x;
                }
                else if (count == 2)
                {
                    if (x == "\n")
                    {
                        if (prev == "*")
                            continue;
                        tempapp.description = num;
                        num = "";
                        count2 = 0;
                        notconfirmed.push_back(tempapp);
                        d.day = d.year = d.month = 0;
                    }
                    else if(x == ',')
                    {
                        if (count2==0)
                        {
                            count2++;
                            time = num.toInt();
                            tempapp.time = time;
                            num = "";
                        }
                        else if (count2 == 1)
                        {
                            count2++;
                            d.year = num.toInt();
                            tempapp.date = d;
                            num = "";

                        }
                        else if(count2 == 2)
                        {
                            count2++;
                            tempapp.address = num;
                            num = "";
                        }
                        else if(count2 == 3)
                        {
                            count2++;
                            tempapp.worker = num;
                            num = "";
                        }
                    }
                    else if(x == "*")
                    {
                        count++;

                    }
                    else if(x == "\r")
                        continue;
                    else if (x == "/")
                    {
                        if (d.day == 0)
                            d.day = num.toInt();
                        else if (d.month == 0)
                            d.month = num.toInt();
                        num = "";

                    }
                    else
                        num = num+x;
                }
    }
    file.close();
}

QVector<Appointment> Customer::getnotconfirmed()
{
    return notconfirmed;
}

QVector<Appointment> Customer::getconfirmed()
{
    return confirmedappointments;
}

void Customer::addconfirmed(Appointment confirmed)
{
    readfile();
    confirmedappointments.append(confirmed);
    QVector<Appointment>::iterator it;
    for (it = notconfirmed.begin();it!=notconfirmed.end();it++ )
    {
        if (it->worker == confirmed.worker && it->time == confirmed.time)
            break;

    }
    notconfirmed.erase(it);
    savetofile();
}

void Customer::decline(Appointment declined)
{
    readfile();

    QVector<Appointment>::iterator it;
    for (it = notconfirmed.begin();it!=notconfirmed.end();it++ )
    {
        if (it->worker == declined.worker && it->time == declined.time)
            break;

    }
    notconfirmed.erase(it);
    savetofile();
}

void Customer::savetofile()
{
    QFile file(""+getUsername()+".txt");
    file.resize(0);
    file.open(QFile::WriteOnly);
    QTextStream stream(&file);


    for(int i = 0;i<confirmedappointments.size();i++)
    {
        stream<<confirmedappointments[i].time<<','<<confirmedappointments[i].date.day<<'/'<<confirmedappointments[i].date.month<<'/'<<confirmedappointments[i].date.year<<','<<
                confirmedappointments[i].address<<','<<confirmedappointments[i].worker<<','<<confirmedappointments[i].description<<'\n';
    }
    stream<<'*'<<'\n';
    for(int i = 0;i<notconfirmed.size();i++)
    {
        stream<<notconfirmed[i].time<<','<<notconfirmed[i].date.day<<'/'<<notconfirmed[i].date.month<<'/'<<notconfirmed[i].date.year<<','<<
                notconfirmed[i].address<<','<<notconfirmed[i].worker<<','<<notconfirmed[i].description<<'\n';
    }
    file.close();
}
