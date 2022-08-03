#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QFont>
#include <QBrush>
class Checkbox: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Checkbox(Qt::GlobalColor);
    void mousePressEvent (QGraphicsSceneMouseEvent * event);
    void maketick();

signals:
    void clicked();
private:
    QGraphicsPixmapItem *tick;

};

#endif // CHECKBOX_H
