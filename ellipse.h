#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "dessin.h"
#include <QRect>

class Ellipse : public Dessin
{
    Q_OBJECT

public:
    Ellipse(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize);

private:
    //QRect rect;
};

#endif // ELLIPSE_H
