#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <QString>
struct Date
{
    int day, month, year;
};

struct Appointment
{
    Date date;
    int time;
    QString customer, address, description,worker;

};

#endif // APPOINTMENT_H
//class Appointment
//{
//public:
//    Appointment();
//};
