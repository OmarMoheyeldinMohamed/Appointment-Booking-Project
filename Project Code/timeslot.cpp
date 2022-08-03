#include "timeslot.h"

Timeslot::Timeslot()
{
    setRect(0, 0, 150, 50);
    setBrush(QBrush(Qt::red));

}

void Timeslot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->brush()== QBrush(Qt::red))
    {
        setBrush(QBrush(Qt::green));

    }
    else
        setBrush(QBrush(Qt::red));
    emit(clicked());
}

bool Timeslot::isavailable()
{
    return (this->brush() == QBrush(Qt::green));
}

