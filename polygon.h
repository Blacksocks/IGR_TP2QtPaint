#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : Shape
{
    private:
        QVector<QPoint> points;
        int maxDist;

    public:
        Polygon(int maxDist) : Shape()
        {
            this->maxDist = maxDist;
        }

        void onMousePressEvent(QMouseEvent * e) {(void)e;}

        void onMouseMoveEvent(QMouseEvent * e) {(void)e;}

        void onMouseReleaseEvent(QMouseEvent * e, bool * newShape)
        {
            if(points.size() > 1)
            {
                if(dist(points.at(0), e->pos()) < maxDist)
                {
                    *newShape = true;
                    return;
                }
            }
            *newShape = false;
            points.append(e->pos());
        }

        void draw(QPainter * painter)
        {
            painter->drawPolygon(QPolygon(points));
        }

        QPainterPath getPath()
        {
            QPainterPath path = QPainterPath();
            path.addPolygon(QPolygon(points));
            return path;
        }

        QPoint * getPtIdxNear(QPoint * p, int maxDist)
        {
            for(int i = 0; i < points.size(); i++)
                if(dist(*p, points.at(i)) < maxDist)
                    return &points[i];
                    //return i+1;
            //return 0;
            return NULL;
        }
};

#endif // POLYGON_H
