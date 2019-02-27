#include "Gamewidget.h"
#include <mainwindow.h>
#include <QPainter>
#include <QTimer>
#include <QWidget>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    timer->setInterval(300);

}

GameWidget::~GameWidget()
{

}

void GameWidget::addPoint(int x, int y)             //adds the newly added points to the vector
{
    int index_counter = 0;
    int check = 0;
    for(int element : qv_x)         //checks if the city is already there
    {

        if(element > (x-10) and element < (x+10))   //checks the surrounding 10 Pixels for another city
        {
            if(qv_y[index_counter] > (y-10) and qv_y[index_counter] < (y+10))
            {
                check++;
            }
        }
        index_counter++;
    }

    if((x > 318 or x < 8) or (y > 408 or y < 8))      //checks if the coordinates are inside our playfield
        check ++;
    if(check == 0)      // if coordinates fulfill requirements -> add city
    {
        qv_x.append(x);
        qv_y.append(y);
        qDebug("Point added.");
        calculateRadius();
    }                     //calculates radius of the points

}

void GameWidget::calculateRadius()
{
    double sum_x = 0;
    double sum_y = 0;
    for (int x : qv_x)
        sum_x += x;
    centrePoint_x = sum_x / qv_x.size();


    for (int x =0; x < qv_y.size(); x++)
        sum_y += qv_y[x];
    centrePoint_y = sum_y / qv_y.size();

}



void GameWidget::paintEvent(QPaintEvent *e)         //paints the needed dots on the field
{

    QPainter painter(this);
    paintCities();
    paintNet();


}


void GameWidget::paintCities()
{
    QPainter painter(this);
    QPen cities(Qt::black);
    cities.setWidth(1);
    painter.setPen(cities);
    painter.setBrush(Qt::green);

    if(qv_x.size()!= 0 and qv_y.size()!=0)              //if not empty, draw new points
    {
        for (int i = 0; i< qv_x.size(); i++)
            painter.drawEllipse(qv_x[i] - 3,qv_y[i] - 3, 6, 6);

    }
}


void GameWidget::solve()
{
    QVector <int> netVector;
    QVector <int> nextGenVector_x, nextGenVector_y;
    QVector <int> changeVector;
    for (int i = 0; i < netPoints_x.size(); i++)
    {
        netVector.push_back(netPoints_x[i]);
        netVector.push_back(netPoints_y[i]);
        //changeVector = changeFunction();
        nextGenVector_x.push_back(changeVector[0] + netPoints_x[i]);
        nextGenVector_y.push_back(changeVector[1] + netPoints_y[i]);


    }
    netPoints_x = nextGenVector_x;
    netPoints_y = nextGenVector_y;
}

void GameWidget::paintNet()
{
    QPainter painter(this);
    QPen net(QColor("red"));
    net.setWidth(3);
    painter.setPen(net);


    if (centrePoint_x != 0 and centrePoint_y !=0)
    {
        painter.drawPoint(centrePoint_x, centrePoint_y);
    }


    for (int i = 0; i < qv_x.size(); i ++)      //calculate number of points on the net
            net_members += (i+1)*2;

    radius = 30;

    QPen ellipse(QColor("black"));              //use this pen for the circle
        ellipse.setWidth(0.1);
        painter.setPen(ellipse);

    if (qv_x.size()!= 0 and qv_y.size()!= 0)        //draw the circle
            painter.drawEllipse(QPointF(centrePoint_x,centrePoint_y),radius,radius);


    QRect gameLayout(3,3,320,410);
    painter.drawRect(gameLayout);;


    // adding points to the circle
    net.setColor(Qt::red);
    net.setBrush(Qt::red);
    painter.setPen(net);

    netPoints_x.clear();    // previous points need to be deleted due to new circle calculation
    netPoints_y.clear();


    for (int i = 0; i < qv_x.size()*2; i++)
    {
        int alpha = 360 * i / (qv_x.size()*2);
        double radiansFactor = M_PI / 180;      // fucking math module is in radians, not in degrees #hourwellspent
        painter.drawEllipse(centrePoint_x + radius * cos(radiansFactor * alpha), centrePoint_y + radius * sin(radiansFactor * alpha), 4, 4);
        netPoints_x.push_back(centrePoint_x + radius * cos(radiansFactor * alpha));
        netPoints_y.push_back(centrePoint_y + radius * sin(radiansFactor * alpha));

    }
}


void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    //ui->bx_x->setValue(e->pos().x());                //assign position on dot to the spinBox
    //ui->bx_y->setValue(e->pos().y());
    addPoint(e->pos().x(),e->pos().y());
    update();
}

/*void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
   onMouseEvent("Move",e->pos());

}*/




