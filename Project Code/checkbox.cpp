#include "checkbox.h"

Checkbox::Checkbox(Qt::GlobalColor color)
{
    setRect(0, 0, 50, 50);
    setBrush(QBrush(color));
    QPixmap pix(":/Files/tick1.png");
    pix = pix.scaledToWidth(50);
    tick = new QGraphicsPixmapItem(this);
    tick->setPixmap(pix);
    tick->setPos(0,5);
    tick->setVisible(false);


}

void Checkbox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit(clicked());

}

void Checkbox::maketick()
{
    if(tick->isVisible())
        tick->setVisible(false);
    else
        tick->setVisible(true);
}
