#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

class ResizableRectItem : public QGraphicsRectItem
{
public:
    ResizableRectItem(const QRectF &rect, qreal resizablePart = 15,
                      const QSizeF &minimumSize = QSizeF(),
                      const QSizeF &maximumSize = QSizeF(1000000, 1000000),
                      const QPen &innerRectPen = Qt::NoPen,
                      const QBrush &innerRectBrush = Qt::NoBrush,
                      QGraphicsItem *parent = 0);


private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF getInnerRect() const;

    // How much of the left, right, top and bottom border is dedicated to
    // resizing, in pixels.
    qreal resizableBorderSize;

    void resizeRect(QGraphicsSceneMouseEvent *event);

    QSizeF minimumSize;
    QSizeF maximumSize;

    QPen innerRectPen;
    QBrush innerRectBrush;
};

#endif // RESIZABLERECTITEM_H
