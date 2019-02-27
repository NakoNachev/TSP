// credits to Mr Bartman aka Felix Lapp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <cmath>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    game(new GameWidget(this))

{
    timer->setInterval(150);
    ui->setupUi(this);
    //ui->bx_x->setReadOnly(true);
    //ui->bx_y->setReadOnly(true);
    ui->bx_x->setValue(pos().x());
    ui->bx_y->setValue(pos().y());
    configureSpinBox(ui->bx_x, -INT_MAX, +INT_MAX);
    configureSpinBox(ui->bx_y, -INT_MAX, +INT_MAX);


    //connect(game,SIGNAL(mousePress(QMouseEvent *e)),SIGNAL(clickedGraph(QMouseEvent *e)));



    //connect(ui->addPointButton,SIGNAL(clicked()),game,SLOT(addPoint(bx_x.value(),bx_y.value())));
    //connect(game,SIGNAL(environmentChanged(bool)),SLOT(addPoint(bx_x.value(),bx_y.value())));
    //connect(game,SIGNAL(environmentChanged(bool)),ui->intervalSpinBox,SLOT(setDisabled(bool)));
    connect(ui->clearButton,SIGNAL(clicked()),SLOT(clearData()));

    ui->gameLayout->addWidget(game);
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}


void MainWindow::clearData()        //removes all dots from the field
{
    qDebug("Cleared");
    game->qv_x.clear();           //clears the city Vector
    game->qv_y.clear();
    game->centrePoint_x = 0;           //clears the radius
    game->centrePoint_y = 0;
    update();

}



