#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // === Actions ===
    // File Actions
    QAction * openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setToolTip(tr("Open file"));
    QAction * saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setToolTip(tr("Save file"));
    QAction * quitAction = new QAction(QIcon(":/images/quit.png"), tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setToolTip(tr("Quit file"));
    // Draw Actions
    QAction * selModeAction = new QAction(tr("&Select Mode"), this);
    selModeAction->setToolTip(tr("Select Mode"));
    QAction * lineDrawAction = new QAction(tr("Draw &Line"), this);
    lineDrawAction->setToolTip(tr("Draw Line"));
    QAction * rectDrawAction = new QAction(tr("Draw &Rectangle"), this);
    rectDrawAction->setToolTip(tr("Draw Rectangle"));
    QAction * ellDrawAction = new QAction(tr("Draw &Ellipse"), this);
    ellDrawAction->setToolTip(tr("Draw Ellipse"));
    QAction * polyDrawAction = new QAction(tr("Draw &Polygon"), this);
    polyDrawAction->setToolTip(tr("Draw Polygon"));
    QAction * moveAction = new QAction(tr("&Move Mode"), this);
    moveAction->setToolTip(tr("Move Points"));
    // Delete
    QAction * delAction = new QAction(QIcon(":/images/eraser.png"), tr("D&elete"), this);
    delAction->setToolTip(tr("Delete last shape"));
    QAction * delAllAction = new QAction(QIcon(":/images/bin.png"), tr("Delete &All"), this);
    delAllAction->setToolTip(tr("Delete all shapes"));

    // === Menu ===
    QMenuBar * menuBar = this->menuBar();
    //File
    QMenu * fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);
    // Draw
    QMenu * drawMenu = menuBar->addMenu(tr("&Draw"));
    drawMenu->addAction(selModeAction);
    drawMenu->addAction(lineDrawAction);
    drawMenu->addAction(rectDrawAction);
    drawMenu->addAction(ellDrawAction);
    drawMenu->addAction(polyDrawAction);
    drawMenu->addAction(moveAction);

    // === ToolBar ===
    ui->mainToolBar->setIconSize(*new QSize(16, 18));
    ui->mainToolBar->addAction(openAction);
    ui->mainToolBar->addAction(saveAction);
    ui->mainToolBar->addAction(delAction);
    ui->mainToolBar->addAction(delAllAction);

    // === Draw Editor ===
    drawEditor = new DrawEditor(this);
    ui->drawLayout->addWidget(drawEditor);

    // === Connections ===
    // File Actions
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quitApp()));
    // Draw Actions
    connect(selModeAction, SIGNAL(triggered()), this, SLOT(selMode()));
    connect(lineDrawAction, SIGNAL(triggered()), this, SLOT(drawLine()));
    connect(rectDrawAction, SIGNAL(triggered()), this, SLOT(drawRect()));
    connect(ellDrawAction, SIGNAL(triggered()), this, SLOT(drawEll()));
    connect(polyDrawAction, SIGNAL(triggered()), this, SLOT(drawPoly()));
    connect(moveAction, SIGNAL(triggered()), this, SLOT(move()));
    // Delete Actions
    connect(delAction, SIGNAL(triggered()), this, SLOT(del()));
    connect(delAllAction, SIGNAL(triggered()), this, SLOT(delAll()));
    // From DrawEditor
    connect(drawEditor, SIGNAL(sigUpdateUi(QPen *)), this, SLOT(updateUi(QPen *)));
}

void MainWindow::updateUi(QPen * p)
{
    QPalette pal = ui->objColor->palette();
    pal.setColor(QPalette::Button, p->color());
    ui->objColor->setAutoFillBackground(true);
    ui->objColor->setPalette(pal);
    ui->objColor->update();
    ui->objSize->setValue(p->width());
    ui->objStyle->setCurrentIndex(p->style());
}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::drawLine()
{
    drawEditor->drawLine();
}

void MainWindow::drawRect()
{
    drawEditor->drawRect();
}

void MainWindow::drawEll()
{
    drawEditor->drawEll();
}

void MainWindow::drawPoly()
{
    drawEditor->drawPoly();
}

void MainWindow::move()
{
    drawEditor->move();
}

void MainWindow::selMode()
{
    drawEditor->selMode();
}

void MainWindow::del()
{
    drawEditor->del();
}

void MainWindow::delAll()
{
    drawEditor->delAll();
}

bool isHexa(QString s)
{
    bool ok;
    s.toUInt(&ok, 16);
    return ok;
}

void MainWindow::on_currColor_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Set Pen Color"), tr("Color: (Hexadecimal)"),
            QLineEdit::Normal, "EF120A", &ok);
    if(!isHexa(text))
    {
        if(ok)
        {
            QMessageBox msgBox;
            msgBox.setText("Value must be hexadecimal.");
            msgBox.exec();
        }
        return;
    }
    if (ok && !text.isEmpty())
    {
        QPalette pal = ui->currColor->palette();
        pal.setColor(QPalette::Button, QColor("#"+text));
        ui->currColor->setAutoFillBackground(true);
        ui->currColor->setPalette(pal);
        ui->currColor->update();
        drawEditor->setCurrColor(new QColor("#"+text));
    }
}

void MainWindow::on_objColor_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Set Pen Color"), tr("Color: (Hexadecimal)"),
            QLineEdit::Normal, "EF120A", &ok);
    if(!isHexa(text))
    {
        if(ok)
        {
            QMessageBox msgBox;
            msgBox.setText("Value must be hexadecimal.");
            msgBox.exec();
        }
        return;
    }
    if (ok && !text.isEmpty())
    {
        QPalette pal = ui->objColor->palette();
        pal.setColor(QPalette::Button, QColor("#"+text));
        ui->objColor->setAutoFillBackground(true);
        ui->objColor->setPalette(pal);
        ui->objColor->update();
        drawEditor->setObjColor(new QColor("#"+text));
    }
}

void MainWindow::quitApp()
{
    QMessageBox msgBox;
    msgBox.setText("Quit confirmation");
    msgBox.setInformativeText("Do you really want to quit the application?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec() == QMessageBox::Yes)
    {
        cout << "Quit Application" << endl;
        QApplication::quit();
    }
}

void QWidget::closeEvent(QCloseEvent * event)
{
    QMessageBox msgBox;
    msgBox.setText("Quit confirmation");
    msgBox.setInformativeText("Do you really want to quit the application?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec() != QMessageBox::Yes)
        event->ignore();
}

MainWindow::~MainWindow()
{
    delete ui;
}
