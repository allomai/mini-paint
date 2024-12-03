#ifndef LINE_H
#define LINE_H

#include "dessin.h"
#include <QLine>
#include <QPainterPathStroker>

class Line : public Dessin
{
    Q_OBJECT
public:
    Line(QPoint startPos, QPoint endPos, QColor color, Qt::PenStyle style, int strokeSize);
    QPainterPath getPath() const override;
    void moveShape(QPoint offset) override;
    QRect getStart() const;
    QRect getEnd() const;
    void setStartPoint(QPoint newStart);
    void setEndPoint(QPoint newEnd);

private:
    int width = 5;
    int height = 5;

    QRect start;
    QRect end;

    QPoint startPos;
    QPoint endPos;
};

#endif // LINE_H
