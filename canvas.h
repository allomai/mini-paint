#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
#include <iostream>
#include <QPainterPath>

#include "dessin.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "interaction.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(int minw, int minh);

public slots:
    void setColor(int id);
    void setShape(int id);
    void setStyle(int id);
    void setInteraction(int id);
    void setStrokeSize(int size);


protected:
    virtual void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;

private:
    const QColor black = QColor(0, 0, 0);        // Black
    const QColor blue = QColor(66, 192, 251);    // #42C0FB
    const QColor green = QColor(166, 215, 133);   // #A6D785
    const QColor orange = QColor(255, 165, 0);    // #FFA500
    const QColor pink = QColor(224, 33, 138);     // #E0218A
    const QColor purple = QColor(128, 0, 128);     // #800080
    const int width = 5;
    const int height = 5;

    QPoint startPos;
    QPoint currentPos;
    QPoint prevPos;

    QColor currentColor = Qt::black;
    Qt::PenStyle currentStyle = Qt::PenStyle::SolidLine;
    Shape currentShape = Shape::LINE;
    Interaction currentInteraction = Interaction::DRAWING;
    int currentStrokeSize = 5;

    bool isDrawing = false;
    bool isPicked = false;
    bool isInShape = false;
    //QList<Dessin*> dessins;
    QMap<int, Dessin*> dessinsMap;
    int nDessins = 0;
    int idClicked;
    int endOrStart = -1;



};

#endif // CANVAS_H
