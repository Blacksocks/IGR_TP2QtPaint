#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : Shape
{
    private:
        QPoint p1;
        QPoint p2;

    public:
        Ellipse() : Shape() {}

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
            painter->drawEllipse(*(new QRect(p1, p2)));
        }

        QPainterPath getPath()
        {
            QPainterPath path = QPainterPath();
            path.addEllipse(QRect(p1, p2));
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

#endif // ELLIPSE_H
