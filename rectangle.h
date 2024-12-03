#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "dessin.h"
#include <QRect>

class Rectangle : public Dessin
{
    Q_OBJECT

public:
    Rectangle(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize);

private:
    //QRect rect;

};

#endif // RECTANGLE_H
