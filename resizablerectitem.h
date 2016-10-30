#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

class ResizableRectItemSettings;

class ResizableRectItem : public QGraphicsRectItem
{
public:
    ResizableRectItem(QRectF rect, const ResizableRectItemSettings *settings, QGraphicsItem *parent = 0);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF getInnerRect() const;
    void resizeRect(QGraphicsSceneMouseEvent *event);
    const ResizableRectItemSettings *settings;
};

#endif // RESIZABLERECTITEM_H
