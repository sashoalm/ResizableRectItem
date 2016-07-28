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

    // The code can probably be drastically simplified, especially the minimum
    // and maximum size enforcement. But this works OK for now.

    QPointF delta = event->pos() - event->lastPos();
    if (resizeDirections.left) {
        setRect(rect().adjusted(delta.x(), 0, 0, 0));

        // Enforce minimum/maximum size.
        if (rect().width() < mMinimumSize.width()) {
            setRect(rect().adjusted(rect().width()-mMinimumSize.width(), 0, 0, 0));
        } else if (rect().width() > mMaximumSize.width()) {
            setRect(rect().adjusted(rect().width()-mMaximumSize.width(), 0, 0, 0));
        }
    } else if (resizeDirections.right) {
        setRect(rect().adjusted(0, 0, delta.x(), 0));

        // Enforce minimum/maximum size.
        if (rect().width() < mMinimumSize.width()) {
            setRect(rect().adjusted(0, 0, -(rect().width()-mMinimumSize.width()), 0));
        } else if (rect().width() > mMaximumSize.width()) {
            setRect(rect().adjusted(0, 0, -(rect().width()-mMaximumSize.width()), 0));
        }
    }

    if (resizeDirections.top) {
        setRect(rect().adjusted(0, delta.y(), 0, 0));

        // Enforce minimum/maximum size.
        if (rect().height() < mMinimumSize.height()) {
            setRect(rect().adjusted(0, rect().height()-mMinimumSize.height(), 0, 0));
        } else if (rect().height() > mMaximumSize.height()) {
            setRect(rect().adjusted(0, rect().height()-mMaximumSize.height(), 0, 0));
        }
    } else if (resizeDirections.bottom) {
        setRect(rect().adjusted(0, 0, 0, delta.y()));

        // Enforce minimum/maximum size.
        if (rect().height() < mMinimumSize.height()) {
            setRect(rect().adjusted(0, 0, 0, -(rect().height()-mMinimumSize.height())));
        } else if (rect().height() > mMaximumSize.height()) {
            setRect(rect().adjusted(0, 0, 0, -(rect().height()-mMaximumSize.height())));
        }
    }
}
