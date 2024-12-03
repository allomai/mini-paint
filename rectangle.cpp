#include "rectangle.h"

Rectangle::Rectangle(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize) {
    this->shape = Shape::RECTANGLE;
    this->color = color;
    this->style = style;
    this->strokeSize = strokeSize;
    this->path.addRect(QRect(startPos, endPos));

    QPainterPathStroker strocker;
    strocker.setWidth(10);
    this ->outPath = strocker.createStroke(path);

}

