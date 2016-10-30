#include "resizablerectitemsettings.h"
#include "resizedirections.h"

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

void ResizableRectItemSettings::validateRect(QRectF *r, const ResizeDirections &resizeDirections) const
{
    // I don't use QRectF because its members can't be manipulated
    // directly.
    qreal left = r->left();
    qreal top = r->top();
    qreal right = left + r->width();
    qreal bottom = top + r->height();

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
        left = qBound(right-maximumSize.width(), left, right-minimumSize.width());
    } else if (resizeDirections.horizontal == resizeDirections.Right) {
        right = qBound(minimumSize.width()+left, right, maximumSize.width()+left);
    }

    if (resizeDirections.vertical == resizeDirections.Top) {
        top = qBound(bottom-maximumSize.height(), top, bottom-minimumSize.height());
    } else if (resizeDirections.vertical == resizeDirections.Bottom) {
        bottom = qBound(minimumSize.height()+top, bottom, maximumSize.height()+top);
    }

    r->setRect(left, top, right-left, bottom-top);
}
