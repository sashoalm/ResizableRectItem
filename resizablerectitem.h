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
        bool left, top, right, bottom;
        bool any() { return left || top || right || bottom; }
    } resizeDirections;

    void resizeRect(QGraphicsSceneMouseEvent *event);

    QSizeF mMinimumSize;
    QSizeF mMaximumSize;
};

#endif // RESIZABLERECTITEM_H
