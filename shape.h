#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <math.h>

class Shape
{
    private:
        QPen pen;
    public:
        Shape() {}
        QPen * getPen(){return &pen;}
        void setPen(QPen p){pen = p;}
        virtual void onMousePressEvent(QMouseEvent * e) = 0;
        virtual void onMouseMoveEvent(QMouseEvent * e) = 0;
        virtual void onMouseReleaseEvent(QMouseEvent * e, bool * newShape) = 0;
        virtual void draw(QPainter * painter) = 0;
        virtual QPoint * getPtIdxNear(QPoint * p, int maxDist) = 0;
        virtual QPainterPath getPath() = 0;
        static int dist(const QPoint p2, const QPoint p1)
        {
            return(sqrt(pow(p2.x()-p1.x(), 2) + pow(p2.y()-p1.y(), 2)));
        }
};

#endif // SHAPE_H
