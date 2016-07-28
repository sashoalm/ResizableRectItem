#include "resizablerectitem.h"
#include <QGraphicsSceneMouseEvent>

ResizableRectItem::ResizableRectItem(const QRectF &rect, qreal resizablePart, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    this->resizablePart = resizablePart;

    // Some big value for maximum size by default.
    mMaximumSize.setWidth(1000000);
    mMaximumSize.setHeight(1000000);
}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qreal widthPart = resizablePart * rect().width() / 2;
    qreal heightPart = resizablePart * rect().height() / 2;
    QRectF innerRect = rect().adjusted(widthPart, heightPart, -widthPart, -heightPart);

    resizeDirections.left = event->pos().x() < innerRect.left();
    resizeDirections.right = event->pos().x() > innerRect.right();
    resizeDirections.top = event->pos().y() < innerRect.top();
    resizeDirections.bottom = event->pos().y() > innerRect.bottom();

    Q_ASSERT(!(resizeDirections.left && resizeDirections.right));
    Q_ASSERT(!(resizeDirections.top && resizeDirections.bottom));

    // If not a resize event, pass it to base class so move event can be implemented.
    if (!resizeDirections.any()) {
        QGraphicsRectItem::mousePressEvent(event);
    }
}

void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // If not a resize event, pass it to base class so move event can be implemented.
    if (!resizeDirections.any()) {
        QGraphicsRectItem::mouseMoveEvent(event);
    } else {
        resizeRect(event);
    }
}

void ResizableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // If not a resize event, pass it to base class so move event can be implemented.
    if (!resizeDirections.any()) {
        QGraphicsRectItem::mouseReleaseEvent(event);
    } else {
        resizeRect(event);
    }
}

void ResizableRectItem::resizeRect(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();

    // The qBound() is used for enforcement of the minimum and maximum sizes.
    // It's derived after solving the following inequalities (example is for
    // left-resizing):
    //
    // newWidth = oldWidth - deltaX (remember when adding +10 to the left border, the width decreases)
    // minimumWidth <= newWidth <= maximumWidth
    // minimumWidth <= oldWidth - deltaX <= maximumWidth
    // minimumWidth - oldWidth <= (-deltaX) <= maximumWidth - oldWidth
    // Reverting the sign reverts the inequality - if a<=b then -a>=-b:
    // -(minimumWidth - oldWidth) >= -(-deltaX) >= -(maximumWidth - oldWidth)
    // Which is equivalent to:
    // oldWidth-maximumWidth <= deltaX <= oldWidth-minimumWidth
    //
    // Ditto for the other 3 directions.

    QPointF delta = event->pos() - event->lastPos();
    if (resizeDirections.left) {
        qreal dx = qBound(rect().width() - maximumSize().width(),
                          delta.x(),
                          rect().width() - minimumSize().width());
        setRect(rect().adjusted(dx, 0, 0, 0));
    } else if (resizeDirections.right) {
        qreal dx = qBound(minimumSize().width() - rect().width(),
                          delta.x(),
                          maximumSize().width() - rect().width());
        setRect(rect().adjusted(0, 0, dx, 0));
    }

    if (resizeDirections.top) {
        qreal dy = qBound(rect().height() - maximumSize().height(),
                          delta.y(),
                          rect().height() - minimumSize().height());
        setRect(rect().adjusted(0, dy, 0, 0));
    } else if (resizeDirections.bottom) {
        qreal dy = qBound(minimumSize().height() - rect().height(),
                          delta.y(),
                          maximumSize().height() - rect().height());
        setRect(rect().adjusted(0, 0, 0, dy));
    }
}
