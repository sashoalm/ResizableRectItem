#include "resizablerectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

static struct {
    enum { HorzNone, Left, Right } horizontal;
    enum { VertNone, Top, Bottom } vertical;
    bool any() { return horizontal || vertical; }
} resizeDirections;

// Horizontal and vertical distance from the cursor position at the time of
// mouse-click to the nearest respective side of the rectangle. Whether
// it's left or right, and top or bottom, depends on which side we'll be
// resizing. We use that to calculate the rectangle from the mouse position
// during the mouse move events.
static qreal horizontalDistance;
static qreal verticalDistance;

ResizableRectItem::ResizableRectItem(const QRectF &rect, qreal resizablePart,
                                     const QSizeF &minimumSize,
                                     const QSizeF &maximumSize,
                                     QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    this->resizablePart = resizablePart;
    this->minimumSize = minimumSize;
    this->maximumSize = maximumSize;
}

void ResizableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF innerRect = getInnerRect();

    // Get the resize-directions.
    const QPointF &pos = event->pos();
    if (pos.x() < innerRect.left()) {
        resizeDirections.horizontal = resizeDirections.Left;
        horizontalDistance = rect().left() - pos.x();
    } else if (pos.x() > innerRect.right()) {
        resizeDirections.horizontal = resizeDirections.Right;
        horizontalDistance = rect().right() - pos.x();
    } else {
        resizeDirections.horizontal = resizeDirections.HorzNone;
    }

    if (pos.y() < innerRect.top()) {
        resizeDirections.vertical = resizeDirections.Top;
        verticalDistance = rect().top() - pos.y();
    } else if (pos.y() > innerRect.bottom()) {
        resizeDirections.vertical = resizeDirections.Bottom;
        verticalDistance = rect().bottom() - pos.y();
    } else {
        resizeDirections.vertical = resizeDirections.VertNone;
    }

    // If not a resize event, pass it to base class so the move-event can be
    // implemented.
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

void ResizableRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen old = painter->pen();
    painter->setPen(Qt::DashLine);
    painter->drawRect(getInnerRect());
    painter->setPen(old);
    QGraphicsRectItem::paint(painter, option, widget);
}

QRectF ResizableRectItem::getInnerRect() const
{
    // Get the inner rect.
    qreal widthPart = resizablePart * rect().width() / 2;
    qreal heightPart = resizablePart * rect().height() / 2;
    return rect().adjusted(widthPart, heightPart, -widthPart, -heightPart);
}

void ResizableRectItem::resizeRect(QGraphicsSceneMouseEvent *event)
{
    // I don't use QRectF because its members can't be manipulated
    // directly.
    qreal left = rect().left();
    qreal top = rect().top();
    qreal right = left + rect().width();
    qreal bottom = top + rect().height();

    // The qBound() is used for enforcement of the minimum and maximum sizes.
    // It's derived after solving the following inequalities (example is for
    // left-resizing):
    //
    // minWidth <= newWidth <= maxWidth
    // minWidth <= right-newLeft <= maxWidth
    // minWidth-right <= -newLeft <= maxWidth-right
    // right-minWidth >= newLeft >= right-maxWidth
    //
    // Ditto for the other 3 directions.

    if (resizeDirections.horizontal == resizeDirections.Left) {
        left = event->pos().x() + horizontalDistance;
        // Enforce minimum/maximum size.
        left = qBound(right-maximumSize.width(), left, right-minimumSize.width());
    } else if (resizeDirections.horizontal == resizeDirections.Right) {
        right = event->pos().x() + horizontalDistance;
        // Enforce minimum/maximum size.
        right = qBound(minimumSize.width()+left, right, maximumSize.width()+left);
    }

    if (resizeDirections.vertical == resizeDirections.Top) {
        top = event->pos().y() + verticalDistance;
        // Enforce minimum/maximum size.
        top = qBound(bottom-maximumSize.height(), top, bottom-minimumSize.height());
    } else if (resizeDirections.vertical == resizeDirections.Bottom) {
        bottom = event->pos().y() + verticalDistance;
        // Enforce minimum/maximum size.
        bottom = qBound(minimumSize.height()+top, bottom, maximumSize.height()+top);
    }

    QRectF newRect(left, top, right-left, bottom-top);
    if (newRect != rect()) {
        // The documentation states this function should be called prior to any changes
        // in the geometry:
        // Prepares the item for a geometry change. Call this function before
        // changing the bounding rect of an item to keep QGraphicsScene's index
        // up to date.
        prepareGeometryChange();

        // For top and left resizing, we move the item's position in the
        // parent. This is because we want any child items it has to move along
        // with it, preserving their distance relative to the top-left corner
        // of the rectangle, because this is the most-expected behavior from a
        // user's point of view.
        // mapToParent() is needed for rotated rectangles.
        setPos(mapToParent(newRect.topLeft() - rect().topLeft()));
        newRect.translate(rect().topLeft() - newRect.topLeft());

        setRect(newRect);
    }
}
