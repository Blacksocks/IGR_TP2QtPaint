#ifndef MYLINE_H
#define MYLINE_H

#include "shape.h"
#include <QLine>
#include <iostream>

class Line : Shape
{
    private:
        QPoint p1;
        QPoint p2;

    public:
        Line() : Shape() {}

        void onMousePressEvent(QMouseEvent * e)
        {
            p1 = e->pos();
            p2 = e->pos();
        }

        void onMouseMoveEvent(QMouseEvent * e)
        {
            p2 = e->pos();
        }

        void onMouseReleaseEvent(QMouseEvent * e, bool * newShape)
        {
            p2 = e->pos();
            *newShape = true;
        }

        void draw(QPainter * painter)
        {
            painter->drawLine(p1, p2);
        }

        QPainterPath getPath()
        {
            QPainterPath path = QPainterPath();
            QVector<QPoint> vect = QVector<QPoint>();
            vect.append(p1);
            vect.append(p2);
            path.addPolygon(QPolygon(vect));
            return path;
        }

        QPoint * getPtIdxNear(QPoint * p, int maxDist)
        {
            if(dist(*p, p1) < maxDist)
                return &p1;
            if(dist(*p, p2) < maxDist)
                return &p2;
            return 0;
        }
};

#endif // MYLINE_H
