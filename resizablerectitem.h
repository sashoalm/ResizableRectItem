#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>

class ResizableRectItem : public QGraphicsRectItem
{
public:
    ResizableRectItem(const QRectF &rect, QGraphicsItem *parent = 0);
};

#endif // RESIZABLERECTITEM_H
