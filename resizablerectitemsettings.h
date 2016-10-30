#ifndef RESIZABLERECTITEMSETTINGS_H
#define RESIZABLERECTITEMSETTINGS_H

#include <QSizeF>
#include <QPen>
#include <QBrush>

class ResizeDirections;

class ResizableRectItemSettings
{
public:
    ResizableRectItemSettings(qreal resizablePart = 15,
                              QSizeF minimumSize = QSizeF(),
                              QSizeF maximumSize = QSizeF(),
                              const QPen &innerRectPen = Qt::NoPen,
                              const QBrush &innerRectBrush = Qt::NoBrush);

    void validateRect(QRectF *r, const ResizeDirections &resizeDirections) const;

    // How much of the left, right, top and bottom border is dedicated to
    // resizing, in pixels.
    qreal resizableBorderSize;

    QPen innerRectPen;
    QBrush innerRectBrush;

private:
    QSizeF minimumSize;
    QSizeF maximumSize;
};

#endif // RESIZABLERECTITEMSETTINGS_H
