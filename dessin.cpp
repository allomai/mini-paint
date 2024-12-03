#include "dessin.h"

Dessin::Dessin(){}

Shape Dessin::getShape() const {
    return shape;
}

QPainterPath Dessin::getPath() const {
    return path;
}

QPainterPath Dessin::getOutPath() const {
    return outPath;
}

void Dessin:: setColor(QColor newColor) {
    color = newColor;
}

void Dessin::setStyle(Qt::PenStyle newStyle) {
    style = newStyle;
}

void Dessin::setStrokeSize (int newSize) {
    strokeSize = newSize;
}

void Dessin::moveShape(QPoint offset) {
    path.translate((offset));
    outPath.translate((offset));
}

void Dessin::setPath(QPainterPath newPath) {
    path = newPath;
}

void Dessin::setOutPath() {
    QPainterPathStroker strocker;
    strocker.setWidth(2*strokeSize);
    this ->outPath = strocker.createStroke(path);
}

void Dessin::draw(QPainter* painter) {
    QPen pen(color);
    pen.setStyle(style);
    pen.setWidth(strokeSize);
    painter->setPen(pen);
    painter->drawPath(path);
}

