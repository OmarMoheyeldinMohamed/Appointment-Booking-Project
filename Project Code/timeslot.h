#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QFont>
#include <QBrush>

class Timeslot: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Timeslot();
    void mousePressEvent (QGraphicsSceneMouseEvent * event);
    bool isavailable();

signals:
    void clicked();

};

#endif // TIMESLOT_H
