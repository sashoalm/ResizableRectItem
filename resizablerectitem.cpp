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
    Q_ASSERT(!(resizeDirections.left && resizeDirections.right));
    Q_ASSERT(!(resizeDirections.top && resizeDirections.bottom));
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "move" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
    resizeRect(event);
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release" << event->pos() << event->lastPos() << event->scenePos() << event->lastScenePos();
    resizeRect(event);
}

void ResizableRectItem::resizeRect(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();

    QPointF delta = event->pos() - event->lastPos();
    if (resizeDirections.left) {
        setRect(rect().adjusted(delta.x(), 0, 0, 0));
    } else if (resizeDirections.right) {
        setRect(rect().adjusted(0, 0, delta.x(), 0));
    }

    if (resizeDirections.top) {
        setRect(rect().adjusted(0, delta.y(), 0, 0));
    } else if (resizeDirections.bottom) {
        setRect(rect().adjusted(0, 0, 0, delta.y()));
    }
}
