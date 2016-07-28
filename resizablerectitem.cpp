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
    } else {
        lastResizePos = event->pos();
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

    prepareGeometryChange();

    QPointF delta = event->pos() - lastResizePos;
    bool wasUpdated = false;
    if (resizeDirections.left) {
        delta.setX(qBound(rect().width() - maximumSize().width(),
                          delta.x(),
                          rect().width() - minimumSize().width()));
        if (delta.x() != 0) {
            setPos(QPointF(pos().x()+delta.x(), pos().y()));
            setRect(rect().adjusted(0, 0, -delta.x(), 0));
        }
    } else if (resizeDirections.right) {
        delta.setX(qBound(minimumSize().width() - rect().width(),
                          delta.x(),
                          maximumSize().width() - rect().width()));
        if (delta.x() != 0) {
            wasUpdated = true;
            setRect(rect().adjusted(0, 0, delta.x(), 0));
        }
    } else {
        // This is needed for lastResizePos to work correctly.
        delta.setX(0);
    }

    if (resizeDirections.top) {
        delta.setY(qBound(rect().height() - maximumSize().height(),
                          delta.y(),
                          rect().height() - minimumSize().height()));
        if (delta.y() != 0) {
            setPos(QPointF(pos().x(), pos().y()+delta.y()));
            setRect(rect().adjusted(0, 0, 0, -delta.y()));
        }
    } else if (resizeDirections.bottom) {
        delta.setY(qBound(minimumSize().height() - rect().height(),
                          delta.y(),
                          maximumSize().height() - rect().height()));
        if (delta.y() != 0) {
            wasUpdated = true;
            setRect(rect().adjusted(0, 0, 0, delta.y()));
        }
    } else {
        // This is needed for lastResizePos to work correctly.
        delta.setY(0);
    }

    if (wasUpdated) {
        // I'm using relative coordinates to move the last resize pos,
        // though I could probably simplify things by just remembering
        // the click-origin point, the original rect, and then using that
        // to calculate how much to add to each side.
        lastResizePos += delta;
    }
}
