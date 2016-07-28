#include "resizablerectitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

ResizableRectItem::ResizableRectItem(const QRectF &rect, qreal resizablePart, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    this->resizablePart = resizablePart;
}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "press" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
    qreal widthPart = resizablePart * rect().width() / 2;
    qreal heightPart = resizablePart * rect().height() / 2;
    QRectF innerRect = rect().adjusted(widthPart, heightPart, -widthPart, -heightPart);
    qDebug() << rect().topLeft() << rect().bottomRight() << innerRect.topLeft() << innerRect.bottomRight();
    resizeDirections.left = event->pos().x() < innerRect.left();
    resizeDirections.right = event->pos().x() > innerRect.right();
    resizeDirections.top = event->pos().y() < innerRect.top();
    resizeDirections.bottom = event->pos().y() > innerRect.bottom();
    qDebug() << resizeDirections.left << resizeDirections.top << resizeDirections.right << resizeDirections.bottom;
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "move" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
}
