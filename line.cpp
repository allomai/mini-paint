#include "line.h"
#include <QDebug>


Line::Line(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize) {
    this->shape = Shape::LINE;
    this->color=color;
    this->style = style;
    this->strokeSize = strokeSize;
    this->path.moveTo(startPos);
    this->path.lineTo(endPos);
    QPainterPathStroker strocker;
    strocker.setWidth(10);
    this ->outPath = strocker.createStroke(path);
    this->start = QRect(startPos.x() - width / 2, startPos.y() - height / 2, width, height);
    this->end = QRect(endPos.x() - width / 2, endPos.y() - height / 2, width, height);
    this->startPos = startPos;
    this->endPos = endPos;

}

void Line::moveShape(QPoint offset) {
    path.translate((offset));
    outPath.translate((offset));
    start.translate(offset);
    end.translate(offset);
    startPos.setX(startPos.x() + offset.x());
    startPos.setY(startPos.y() + offset.y());
    endPos.setX(endPos.x() + offset.x());
    endPos.setY(endPos.y() + offset.y());
}

QPainterPath Line::getPath() const {
    return outPath;
}

QRect Line::getStart() const {
    return start;
}

QRect Line::getEnd() const {
    return end;
}


void Line::setStartPoint(QPoint newStart) {
    this->startPos = newStart;
    path.clear();
    path.moveTo(startPos);
    path.lineTo(endPos);
    setOutPath();
}

void Line::setEndPoint(QPoint newEnd) {
    this->endPos = newEnd;
    path.clear();
    path.moveTo(startPos);
    path.lineTo(endPos);
    setOutPath();
}




