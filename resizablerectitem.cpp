#include "resizablerectitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

ResizableRectItem::ResizableRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{

}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "press" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "move" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
}
