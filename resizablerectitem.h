#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>

class ResizableRectItem : public QGraphicsRectItem
{
public:
    ResizableRectItem(const QRectF &rect, qreal resizablePart, QGraphicsItem *parent = 0);
    void setMinimumSize(const QSizeF &size) { this->mMinimumSize = size; }
    void setMaximumSize(const QSizeF &size) { this->mMaximumSize = size; }
    QSizeF minimumSize() const { return mMinimumSize; }
    QSizeF maximumSize() const { return mMaximumSize; }

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // How much of the border is dedicated to resizing. For example,
    // if we have rectangle (10,20,210,120) and resizablePart=0.15,
    // then the rect size is 200x100 pixels, and 15% of that is dedicated
    // to resizing, which is 30x15 pixels. This is 15 pixels each from
    // the left and right border, and 7.5 pixels each from the top and
    // bottom border are dedicated to resizing. Clicking anywhere inside
    // the inner rectangle (25,27.5,195,112.5) will move the rectangle.
    // Clicking anywhere outside of (25,27.5,195,112.5) but inside of
    // (10,20,210,120) will cause a resize event.
    qreal resizablePart;

    struct {
        enum { HorzNone, Left, Right } horizontal;
        enum { VertNone, Top, Bottom } vertical;
        bool any() { return horizontal || vertical; }
    } resizeDirections;

    // Horizontal and vertical distance from the cursor position at the time of
    // mouse-click to the nearest respective side of the rectangle. Whether
    // it's left or right, and top or bottom, depends on which side we'll be
    // resizing. We use that to calculate the rectangle from the mouse position
    // during the mouse move events.
    qreal horizontalDistance;
    qreal verticalDistance;

    void resizeRect(QGraphicsSceneMouseEvent *event);

    QSizeF mMinimumSize;
    QSizeF mMaximumSize;
};

#endif // RESIZABLERECTITEM_H
