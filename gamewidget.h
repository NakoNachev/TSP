#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class QSpinBox;
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    //void addPoint(int x, int y);    //can be found in  public slots
    void calculateRadius();
    ~GameWidget();
    QVector <int> qv_x,qv_y,netPoints_x,netPoints_y; // vectors for coordinates
    double centrePoint_x, centrePoint_y;


public slots:
    void addPoint(int x, int y);


signals:
    void environmentChanged(bool ok);



private:

    QTimer *timer;
    int *net_members;

    double radius;
    double circumference = 2*radius*3.14;
    //double net_distance = circumference/(qv_x.size()*2);        //distance between the points on the elastic net


protected:
    void paintEvent(QPaintEvent *e);

    //void mouseMoveEvent(QMouseEvent *e);
    void onMouseEvent(const QString &eventName, const QPoint &pos);
    void mousePressEvent(QMouseEvent *e);
    void paintCities();
    void paintNet();
    void solve();
};

#endif // GAMEWIDGET_H
