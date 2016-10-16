#ifndef DRAWEDITOR_H
#define DRAWEDITOR_H

#define SELECT_DIST     10

#include "shape.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QtGui>

class DrawEditor : public QWidget
{
    Q_OBJECT

    enum mode {WAIT, SELECT, DRAW, MOVE};
    enum shape {NONE, LINE, RECT, ELL, POLY};

    private:
        QWidget * parent;
        QList<Shape *> shapes;
        Shape * selShape; // selected shape
        QPoint * selPoint; // selected point
        QRect * cursor0; // pointer representation (position 0:0)
        QPen pen;
        int mode;
        int shape;
        bool newShape;
    public:
        DrawEditor(QWidget * parent);
        void drawLine();
        void drawRect();
        void drawEll();
        void drawPoly();
        void move();
        void selMode();
        void del();
        void delAll();
        void setCurrColor(QColor *);
        void setCurrSize(int);
        int getCurrSize();
        void setCurrStyle(Qt::PenStyle);
        void setObjColor(QColor *);
        void setObjSize(int);
        int getObjSize();
        void setObjStyle(Qt::PenStyle);
    protected:
        virtual void paintEvent(QPaintEvent *e);
        void mouseReleaseEvent(QMouseEvent*);
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
    signals:
        void sigUpdateUi(QPen *);
};

#endif // DRAWEDITOR_H
