#ifndef RESIZABLERECTITEMSETTINGS_H
#define RESIZABLERECTITEMSETTINGS_H

#include <QSizeF>
#include <QPen>
#include <QBrush>

class ResizableRectItemSettings
{
public:
    ResizableRectItemSettings(qreal resizablePart = 15,
                              QSizeF minimumSize = QSizeF(),
                              QSizeF maximumSize = QSizeF(),
                              const QPen &innerRectPen = Qt::NoPen,
                              const QBrush &innerRectBrush = Qt::NoBrush);

    // How much of the left, right, top and bottom border is dedicated to
    // resizing, in pixels.
    qreal resizableBorderSize;

    QSizeF minimumSize;
    QSizeF maximumSize;

    QPen innerRectPen;
    QBrush innerRectBrush;
};

#endif // RESIZABLERECTITEMSETTINGS_H
