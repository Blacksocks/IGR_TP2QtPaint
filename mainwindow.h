#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "draweditor.h"
#include <QMainWindow>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow * ui;
        DrawEditor * drawEditor;

    public slots:
        void openFile();
        void saveFile();
        void quitApp();
        void drawLine();
        void drawRect();
        void drawEll();
        void drawPoly();
        void move();
        void selMode();
        void del();
        void delAll();
        void on_currColor_clicked();
        void on_currSize_valueChanged(int v){drawEditor->setCurrSize(v);update();}
        void on_currStyle_currentIndexChanged(int i){drawEditor->setCurrStyle((Qt::PenStyle)i);update();}
        void on_objColor_clicked();
        void on_objSize_valueChanged(int v){drawEditor->setObjSize(v);update();}
        void on_objStyle_currentIndexChanged(int i){drawEditor->setObjStyle((Qt::PenStyle)i);update();}
        void updateUi(QPen *);
};

#endif // MAINWINDOW_H
