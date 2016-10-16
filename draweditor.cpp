#include "draweditor.h"
#include <QMessageBox>

DrawEditor::DrawEditor(QWidget * parent) : QWidget()
{
    this->parent = parent;
    setMinimumSize(100, 100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    pen = *(new QPen(QColor("#000000"), 1));
    selShape = NULL;
    selPoint = NULL;
    cursor0 = new QRect(QPoint(-SELECT_DIST, -SELECT_DIST), QPoint(SELECT_DIST, SELECT_DIST));
    mode = WAIT;
    shape = NONE;
    newShape = true;
}

void DrawEditor::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);

    for(int i = 0; i < shapes.size(); i++)
    {
        Shape * s = shapes.at(i);
        painter.setPen(*(s->getPen()));
        s->draw(&painter);
    }
}

void DrawEditor::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (mode == DRAW)
        {
            if(newShape)
            {
                switch(shape)
                {
                    case LINE : selShape = (Shape *)(new Line());break;
                    case RECT : selShape = (Shape *)(new Rectangle());break;
                    case ELL : selShape = (Shape *)(new Ellipse());break;
                    case POLY : selShape = (Shape *)(new Polygon(SELECT_DIST));break;
                    default : return;
                }
                shapes.push_back(selShape);
                selShape->setPen(pen);
            }
            selShape->onMousePressEvent(e);
            update();
        }
        else if (mode == MOVE && selPoint == NULL)
        {
            QPoint pos = e->pos();
            for(int i = 0; i < shapes.size(); i++)
                if((selPoint = shapes.at(i)->getPtIdxNear(&(pos), SELECT_DIST)) != NULL)
                    break;
        }
        if (mode == SELECT || mode == MOVE)
        {
            for(int i = 0; i < shapes.size(); i++)
            {
                QPainterPathStroker qpp;
                QPainterPath outline = qpp.createStroke(shapes.at(i)->getPath());
                if(outline.intersects(cursor0->translated(e->pos())))
                {
                    selShape = shapes.at(i);
                    emit sigUpdateUi(selShape->getPen());
                    break;
                }
            }
        }
    }
}

void DrawEditor::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        if(mode == DRAW && selShape != NULL)
        {
            selShape->onMouseMoveEvent(e);
            update();
        }
        else if(mode == MOVE && selPoint != NULL)
        {
            selPoint->setX(e->pos().x());
            selPoint->setY(e->pos().y());
            update();
        }
    }
}

void DrawEditor::mouseReleaseEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        if(mode == DRAW && selShape != NULL)
        {
            selShape->onMouseReleaseEvent(e, &newShape);
            update();
        }
        else if(mode == MOVE && selPoint != NULL)
        {
            selPoint->setX(e->pos().x());
            selPoint->setY(e->pos().y());
            selPoint = NULL;
            update();
        }
    }
}

void DrawEditor::drawLine()
{
    mode = DRAW;
    shape = LINE;
}

void DrawEditor::move()
{
    mode = MOVE;
}

void DrawEditor::selMode()
{
    mode = SELECT;
}

void DrawEditor::drawRect()
{
    mode = DRAW;
    shape = RECT;
}

void DrawEditor::drawEll()
{
    mode = DRAW;
    shape = ELL;
}

void DrawEditor::drawPoly()
{
    mode = DRAW;
    shape = POLY;
}

void DrawEditor::del()
{
    if(shapes.size() > 0)
        shapes.pop_back();
    update();
}

void DrawEditor::delAll()
{
    while(shapes.size() > 0)
        shapes.pop_back();
    update();
}

void DrawEditor::setCurrColor(QColor * newColor)
{
    pen.setColor(*newColor);
}

void DrawEditor::setCurrSize(int newSize)
{
    pen.setWidth(newSize);
}

int DrawEditor::getCurrSize()
{
    return pen.width();
}

void DrawEditor::setCurrStyle(Qt::PenStyle newStyle)
{
    pen.setStyle(newStyle);
}

void DrawEditor::setObjColor(QColor * newColor)
{
    if(selShape != NULL)
        selShape->getPen()->setColor(*newColor);
}

void DrawEditor::setObjSize(int newSize)
{
    if(selShape != NULL)
        selShape->getPen()->setWidth(newSize);
}

int DrawEditor::getObjSize()
{
    if(selShape != NULL)
        return selShape->getPen()->width();
    return 0;
}

void DrawEditor::setObjStyle(Qt::PenStyle newStyle)
{
    if(selShape != NULL)
        selShape->getPen()->setStyle(newStyle);
}

