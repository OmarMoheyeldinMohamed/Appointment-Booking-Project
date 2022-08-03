#include "timetable.h"

Timetable::Timetable()
{
    setRect(0, 0,1050, 600);
    setBrush(QBrush(Qt::black));

    for (int i = 0; i<12; i++)
    {
        QVector<bool> temp;
        for (int j = 0; j<7; j++)
            temp.push_back(false);
        available.push_back(temp);
    }


}

void Timetable::makeslots()
{
    for (int i = 0; i<12; i++)
    {
        QVector<Timeslot*> temp;
        for (int j = 0; j<7; j++)
        {
            Timeslot *slot = new Timeslot;
            temp.push_back(slot);
            this->scene()->addItem(slot);
            connect(slot, SIGNAL(clicked()), this, SLOT(changeavailable()));
            slot->setPos(130+150*j, 175+50*i);
        }
        table.push_back(temp);

    }
    for (int i = 0; i<12; i++)
    {
        QFont writefont3("comic sans", 10);
        QGraphicsTextItem *time= new QGraphicsTextItem(QString(QString::number(9+i)+":00 - "+QString::number(9+i+1)+":00"));
        time->setFont(writefont3);
        time->setPos(10, 190+50*i);
        time->setDefaultTextColor(Qt::white);
        scene()->addItem(time);
    }
}

QVector<QVector<bool> > Timetable::getavailability()
{
    return available;
}


void Timetable::changeavailable()
{
    Timeslot *t = dynamic_cast<Timeslot*>(QObject::sender());
    for (int i = 0; i<12; i++)
        for (int j = 0; j<7; j++)
            if (table[i][j] == t)
            {
                if (available[i][j])
                    available[i][j] = false;
                else
                    available[i][j] = true;
            }

}
