#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "appointment.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
class Customer : public User
{
public:
    Customer();
    Customer(QString Username, QString Password);
    UserType gettype();
    void addpending(Appointment);
    void readfile();
    QVector<Appointment> getnotconfirmed();
    QVector<Appointment> getconfirmed();
    void addconfirmed(Appointment confirmed);
    void decline(Appointment declined);
private:
    QVector<Appointment> confirmedappointments;
    QVector<Appointment> notconfirmed;
    void savetofile();
};

#endif // CUSTOMER_H
