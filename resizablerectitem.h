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

    void resizeRect(QGraphicsSceneMouseEvent *event);

    QSizeF mMinimumSize;
    QSizeF mMaximumSize;

    // The last position under which we actually resized. We use that to avoid
    // the nasty effect where the cursor moves to the right, past the maximum
    // size, the rect stops resizing, and then as soon as the cursor reverses
    // direction to the left, the item starts shrinking.
    // We want the mouse cursor to be always at the same distance from the
    // side(s) which are being resized.
    QPointF lastResizePos;
};

#endif // RESIZABLERECTITEM_H
