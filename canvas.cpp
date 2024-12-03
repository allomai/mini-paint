#include "canvas.h"
#include <QDebug>

Canvas::Canvas(int minw, int minh)
{
    setMinimumSize(minw, minh);
}

void Canvas::setColor(int id)
{

    switch(id) {
        case 1:
            currentColor = black;
            break;
        case 2:
            currentColor = blue;
            break;
        case 3:
            currentColor = green;
            break;
        case 4:
            currentColor = orange;
            break;
        case 5:
            currentColor = pink;
            break;
        case 6:
            currentColor = purple;
            break;
    }

        if (currentInteraction == Interaction::SELECTING) {
            Dessin* dessin = dessinsMap.value(idClicked);
            dessin->setColor(currentColor);
        }

    update();
}

void Canvas::setShape(int id)
{
    switch (id) {
    case 1:
        currentShape = Shape::LINE;
        break;
    case 2:
        currentShape = Shape::RECTANGLE;
        break;
    case 3:
        currentShape = Shape::ELLIPSE;
        break;
    }
    update();
}

void Canvas::setStyle(int id)
{
    switch (id) {
    case 1:
        currentStyle = Qt::PenStyle::SolidLine;
        break;
    case 2:
        currentStyle = Qt::PenStyle::DashLine;
        break;
    case 3:
        currentStyle = Qt::PenStyle::DotLine;
        break;
    }

    if (currentInteraction == Interaction::SELECTING) {
        Dessin* dessin = dessinsMap.value(idClicked);
        dessin->setStyle(currentStyle);
    }

    update();
}

void Canvas::setInteraction(int id) {
    switch (id) {
    case 1:
        currentInteraction = Interaction::DRAWING;
        break;
    case 2:
        currentInteraction = Interaction::SELECTING;
        break;
    case 3:
        currentInteraction = Interaction::RESIZING;
        break;
    }
    update();
}

void Canvas::setStrokeSize(int size) {
    currentStrokeSize = size;

    if (currentInteraction == Interaction::SELECTING) {
        Dessin* dessin = dessinsMap.value(idClicked);
        dessin->setStrokeSize(currentStrokeSize);
    }

    update();
}

void Canvas::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);
    QPen pen(currentColor);
    pen.setWidth(currentStrokeSize);
    pen.setStyle(currentStyle);
    painter.setPen(pen);

    for (Dessin *dessin : dessinsMap.values()) {
        dessin->draw(&painter);
    }
        if (isDrawing)
        {
            Dessin* dessin = nullptr;
            switch(currentShape) {
            case Shape::LINE:
                dessin = new Line(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessin->draw(&painter);
                break;
            case Shape::RECTANGLE:
                dessin = new Rectangle(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessin->draw(&painter);
                break;
            case Shape::ELLIPSE:
                dessin = new Ellipse(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessin->draw(&painter);
                break;
            }

        }



}

void Canvas::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton){
        QPoint pos = e->pos();
        startPos = pos;

        switch(currentInteraction) {

        case Interaction::DRAWING:

            isDrawing = true;
            currentPos = startPos;
            break;

        case Interaction::SELECTING:

            for (Dessin *dessin : dessinsMap.values()) {
                if (dessin->getPath().contains(pos)) {
                    idClicked = dessinsMap.key(dessin);
                    isInShape = true;
                    break;
                }
            }

        case Interaction::RESIZING:

            for (Dessin *dessin : dessinsMap.values()) {

                if (dessin->getShape() == Shape::LINE) {
                    Line* line = dynamic_cast<Line*>(dessin);

                    QRect start = line->getStart();
                    QRect end = line->getEnd();

                    if (start.contains(pos)) {

                        isPicked = true;
                        idClicked = dessinsMap.key(dessin);
                        prevPos = pos;
                        endOrStart = 0;
                        qDebug() << "borderline start!";
                        break;

                    } else if (end.contains(pos)) {

                        isPicked = true;
                        idClicked = dessinsMap.key(dessin);
                        prevPos = pos;
                        endOrStart = 1;
                        qDebug() << "borderline end!";
                        break;
                    }


                } else {
                    if (dessin->getOutPath().contains(pos)) {
                        isPicked = true;
                        idClicked = dessinsMap.key(dessin);
                        prevPos = pos;
                        qDebug() << "border!";
                        break;
                    }

                }

            }
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* e)
{
    currentPos = e->pos();

    switch(currentInteraction) {

    case Interaction::DRAWING:
        update();
        break;

    case Interaction::SELECTING:

        if (isInShape) {
            Dessin* dessin = dessinsMap.value(idClicked);
            QPoint offset(currentPos.x() - startPos.x(),
                          currentPos.y() - startPos.y());
            dessin->moveShape(offset);
            startPos = currentPos;
            update();
        }
        break;

    case Interaction::RESIZING:

        if (isPicked) {
            Dessin* dessin = dessinsMap.value(idClicked);

            int direction = 44;
            if (currentPos.x() > prevPos.x()) {
                direction = 0;
            } else if (currentPos.x() < prevPos.x()) {
                direction = 1;
            }
            update();

            if (currentPos.y() > prevPos.y()) {
                direction = 2;
            } else if (currentPos.y() < prevPos.y()) {
                direction = 3;
            }
            update();


            if (dessin->getShape() == Shape::LINE) {
                Line* line = dynamic_cast<Line*>(dessin);

                if (line) {
                    QPoint offset(currentPos.x() - prevPos.x(), currentPos.y() - prevPos.y());

                    if (endOrStart == 0) {
                        line->setStartPoint(currentPos);

                    } else if (endOrStart == 1) {
                        line->setEndPoint(currentPos);
                    }

                    update();
                    prevPos = currentPos;
                }

            } else {

                QRectF rect = dessin->getPath().boundingRect();

                if (direction == 0) {
                    qreal newWidth = rect.width() + (currentPos.x() - prevPos.x());
                    if (newWidth > 0) {
                        rect.setWidth(newWidth);
                    }
                } else if (direction == 1) {
                    qreal deltaX = currentPos.x() - prevPos.x();
                    qreal newX = rect.x() + deltaX;
                    qreal newWidth = rect.right() - newX;

                    if (newWidth > 0) {
                        rect.setX(newX);
                        rect.setWidth(newWidth);
                    }
                }

                if (direction == 2) {
                    qreal newHeight = rect.height() + (currentPos.y() - prevPos.y());
                    if (newHeight > 0) {
                        rect.setHeight(newHeight);
                    }
                } else if (direction == 3) {
                    qreal deltaY = currentPos.y() - prevPos.y();
                    qreal newY = rect.y() + deltaY;
                    qreal newHeight = rect.bottom() - newY;

                    if (newHeight > 0) {
                        rect.setY(newY);
                        rect.setHeight(newHeight);
                    }
                }

                QPainterPath newPath;

                if (dessin->getShape() == Shape::RECTANGLE) {
                    newPath.addRect(rect);

                } else if (dessin->getShape() == Shape::ELLIPSE) {
                    newPath.addEllipse(rect);
                }

                dessin->setPath(newPath);
                dessin->setOutPath();
                update();
            }

            prevPos = currentPos;

        }

        break;
    }


}

void Canvas::mouseReleaseEvent(QMouseEvent* e) {

    if (e->button() == Qt::LeftButton) {
        Dessin* dessin = nullptr;

        switch (currentInteraction) {

        case Interaction::DRAWING:
            isDrawing = false;
            currentPos = e->pos();

            switch (currentShape) {

            case Shape::LINE:
                dessin = new Line(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessinsMap.insert(nDessins, dessin);
                nDessins++;
                break;

            case Shape::RECTANGLE:
                dessin = new Rectangle(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessinsMap.insert(nDessins, dessin);
                nDessins++;
                break;

            case Shape::ELLIPSE:
                dessin = new Ellipse(startPos, currentPos, currentColor, currentStyle, currentStrokeSize);
                dessinsMap.insert(nDessins, dessin);
                nDessins++;
                break;
            }

            update();
            break;

        case Interaction::SELECTING:
            isInShape = false;
            break;

        case Interaction::RESIZING:
            isPicked = false;
            endOrStart = -1;
            break;

        }

    }

}
