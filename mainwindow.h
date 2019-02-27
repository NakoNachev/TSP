#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QWidget>
#include <QPaintEvent>
#include <Gamewidget.h>

namespace Ui {
class MainWindow;
}

class QSpinBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT     // macro

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void environmentChanged(bool ok);

public slots:
    void clearData();

private:
    Ui::MainWindow *ui;
    //GameWidget *game;
    QTimer *timer;
    GameWidget* game;


protected:

    void configureSpinBox(QSpinBox *spinBox, int min, int max ) const;


};

#endif // MAINWINDOW_H
