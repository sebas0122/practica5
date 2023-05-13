#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void aviso(int);

public slots:
    void animar();
    void aumentarPunt();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsEllipseItem* circle;
    QGraphicsRectItem *rectItemgalleta;
    QGraphicsRectItem *rectItempared;
    QGraphicsLineItem* l2;
    QGraphicsLineItem* l3;
    QGraphicsLineItem* l4;
    QTimer *timer;

    std::vector<QGraphicsRectItem*> galletas;
    std::vector<QGraphicsRectItem*> paredes;


    int puntuacion;

    bool moverIx1=false;
    bool moverDx1=false;
    bool moverUy1=false;
    bool moverDy1=false;
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
};
#endif // MAINWINDOW_H
