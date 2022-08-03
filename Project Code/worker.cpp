#include "worker.h"

Worker::Worker()
{
}

Worker::Worker(QString Username, QString Password):User(Username, Password)
{

}

UserType Worker::gettype()
{
    return work;
}

void Worker::settimetable(Timetable* x)
{
    tbl = x;
}

void Worker::savenewtimes()
{
    QVector<QVector<bool>> x = tbl->getavailability();

    for (int i =0; i<7;i++)
    {
        QVector<int> tmp;
        for (int j = 0; j<12;j++)
        {
            if (x[j][i] == true)
                tmp.push_back(9+j);
        }
        availability.push_back(tmp);
    }
    savetofile();


}

void Worker::setJob(QString x)
{
    Job = x;
}

void Worker::readfile()
{
    QFile file(""+getUsername()+".txt");
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    confirmedappointments.clear();
    notconfirmed.clear();
    QString x;
    int count = 0, count2 = 0;
    QVector<int> tmp;
    availability.clear();
    QString num = "";
    bool job = false;
    QString j ="";
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
        if (job){
            if (count == 0)
            {
                if (x == "\n")
                {
                    if (num !="")
                        tmp.push_back(num.toInt());
                    num = "";
                    availability.push_back(tmp);
                    tmp.clear();
                }
                else
                    if (x == "\r")
                    {
                        continue;
                    }
                else if(x==",")
                    {
                        tmp.push_back(num.toInt());
                        num = "";
                    }
                else if(x == "*")
                        count++;
                else
                        num = num+x;

            }
            else if(count == 1)
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
                        tempapp.customer = num;
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
                        tempapp.customer = num;
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
        else
        {
            if (x == "\n")
            {
                job = true;
                Job = j;
            }
            else
                if(x == "\r")
                    continue;
            else
                    j = j+x;
        }

    }

    file.close();
}

QVector<Appointment> Worker::getappointmentsconfirmed()
{
    return confirmedappointments;
}

QVector<Appointment> Worker::getnotconfirmed()
{
    return notconfirmed;
}

void Worker::addpending(Appointment x)
{
    readfile();
    notconfirmed.append(x);
    savetofile();
}

void Worker::addconfirmed(Appointment confirmed)
{
    readfile();
    confirmedappointments.append(confirmed);
    QVector<Appointment>::iterator it;
    for (it = notconfirmed.begin();it!=notconfirmed.end();it++ )
    {
        if (it->customer == confirmed.customer&& it->time == confirmed.time)
            break;

    }
    notconfirmed.erase(it);
    savetofile();
}

void Worker::decline(Appointment declined)
{
    readfile();

    QVector<Appointment>::iterator it;
    for (it = notconfirmed.begin();it!=notconfirmed.end();it++ )
    {
        if (it->customer == declined.customer&& it->time == declined.time)
            break;

    }
    notconfirmed.erase(it);
    savetofile();
}

void Worker::savetofile()
{
    QFile file(""+getUsername()+".txt");
    file.resize(0);
    file.open(QFile::WriteOnly);
    QTextStream stream(&file);
    stream<<Job<<'\n';

    for (int i=0; i<availability.size();i++)
    {
        for(int j = 0; j<availability[i].size()-1;j++)
        {
            stream<<availability[i][j]<<',';
        }
        if (availability[i].size() >=1)
            stream<<availability[i][availability[i].size()-1];
        stream<<'\n';
    }
    stream<<'*'<<'\n';
    for(int i = 0;i<confirmedappointments.size();i++)
    {
        stream<<confirmedappointments[i].time<<','<<confirmedappointments[i].date.day<<'/'<<confirmedappointments[i].date.month<<'/'<<confirmedappointments[i].date.year<<','<<
                confirmedappointments[i].address<<','<<confirmedappointments[i].customer<<','<<confirmedappointments[i].description<<'\n';
    }
    stream<<'*'<<'\n';
    for(int i = 0;i<notconfirmed.size();i++)
    {
        stream<<notconfirmed[i].time<<','<<notconfirmed[i].date.day<<'/'<<notconfirmed[i].date.month<<'/'<<notconfirmed[i].date.year<<','<<
                notconfirmed[i].address<<','<<notconfirmed[i].customer<<','<<notconfirmed[i].description<<'\n';
    }
    file.close();
}
