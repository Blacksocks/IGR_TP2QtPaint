#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include <QRect>

class Rectangle : Shape
{
    private:
        QPoint p1;
        QPoint p2;

    public:
        Rectangle() : Shape() {}

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
            painter->drawRect(*(new QRect(p1, p2)));
        }

        QPainterPath getPath()
        {
            QPainterPath path = QPainterPath();
            path.addRect(QRect(p1, p2));
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

#endif // RECTANGLE_H
