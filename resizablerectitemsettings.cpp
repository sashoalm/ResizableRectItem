#include "resizablerectitemsettings.h"

static void ensureAscending(const qreal &a, qreal *b)
{
    Q_ASSERT(a <= *b);
    if (a > *b) {
        *b = a;
    }
}

static void ensureAscending(const QSizeF &a, QSizeF *b)
{
    ensureAscending(a.width(), &b->rwidth());
    ensureAscending(a.height(), &b->rheight());
}

ResizableRectItemSettings::ResizableRectItemSettings(qreal resizablePart, QSizeF minimumSize, QSizeF maximumSize, const QPen &innerRectPen, const QBrush &innerRectBrush)
{
    // Give some sensible defaults to empty min/max sizes.
    if (minimumSize.isEmpty()) {
        minimumSize = QSizeF(resizablePart, resizablePart);
    }
    if (maximumSize.isEmpty()) {
        maximumSize = QSizeF(1000000, 1000000);
    }

    ensureAscending(0, &resizablePart);
    ensureAscending(QSizeF(2*resizablePart, 2*resizablePart), &minimumSize);
    ensureAscending(minimumSize, &maximumSize);

    // After all has been validated, assign the variables.
    this->resizableBorderSize = resizablePart;
    this->minimumSize = minimumSize;
    this->maximumSize = maximumSize;
    this->innerRectPen = innerRectPen;
    this->innerRectBrush = innerRectBrush;
}
