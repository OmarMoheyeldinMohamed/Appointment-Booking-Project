#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "timeslot.h"
#include <QVector>
#include <QObject>
#include "QGraphicsScene"
class Timetable:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Timetable();
    void makeslots();
    QVector<QVector<bool>> getavailability();
public slots:
    void changeavailable();
private:
QVector<QVector<Timeslot*>> table;
QVector<QVector<bool>> available;
};

#endif // TIMETABLE_H
