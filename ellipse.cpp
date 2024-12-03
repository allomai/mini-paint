#include "ellipse.h"

Ellipse::Ellipse(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize) {
    this->shape = Shape::ELLIPSE;
    this->color = color;
    this->style = style;
    this->strokeSize = strokeSize;
    this->path.addEllipse(QRect(startPos, endPos));
    QPainterPathStroker strocker;
    strocker.setWidth(10);
    this ->outPath = strocker.createStroke(path);

}




