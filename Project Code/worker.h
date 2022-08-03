#ifndef WORKER_H
#define WORKER_H

#include "user.h"
#include <QVector>
#include "timetable.h"
#include <QFile>
#include <QTextStream>
#include "appointment.h"

class Worker : public User
{
public:
    Worker();
    Worker(QString Username, QString Password);
    UserType gettype();
    QVector<QVector<int>> availability;
    void settimetable(Timetable* x);
    void savenewtimes();
    void setJob(QString x);
    void readfile();
    QVector<Appointment> getappointmentsconfirmed();
    QVector<Appointment> getnotconfirmed();
    void addpending(Appointment);
    void addconfirmed(Appointment confirmed);
    void decline(Appointment declined);
private:
    Timetable *tbl;
    QVector<Appointment> confirmedappointments;
    QVector<Appointment> notconfirmed;
    void savetofile();
    QString Job;

};

#endif // WORKER_H
