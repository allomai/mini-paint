#ifndef DESSIN_H
#define DESSIN_H

#include <QObject>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QPainterPath>
#include "shape.h"

class Dessin : public QObject
{
    Q_OBJECT
public:
    Dessin();
    virtual ~Dessin() = default;
    virtual void draw(QPainter *painter);
    virtual void moveShape(QPoint offset);
    virtual QPainterPath getPath() const;
    QPainterPath getOutPath() const;
    Shape getShape() const;
    void setColor(QColor newColor);
    void setStyle(Qt::PenStyle newStyle);
    void setPath(QPainterPath newPath);
    void setStrokeSize (int newSize);
    void setOutPath();

protected:
    QColor color = Qt::black;
    Qt::PenStyle style = Qt::PenStyle::SolidLine;
    Shape shape;
    int strokeSize = 5;
    QPainterPath path;
    QPainterPath outPath;
    QPainterPath inPath;
    const qreal shrinkFactor = 0.9;



};

#endif // DESSIN_H
