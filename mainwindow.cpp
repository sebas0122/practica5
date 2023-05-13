#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(animar()));
    connect(this,SIGNAL(aviso(int)),this,SLOT(aumentarPunt()));

    timer->start(60);

    scene=new QGraphicsScene(0,0,930,840);
    ui->graphicsView->setScene(scene);

    int i=0;
    int j=0;
    int tablero[31][28]={};
    for (int j=0;j<28;j++){
        i=0;
        tablero[i][j]=1;
    }
    for (int j=0;j<28;j++){
        i=1;
        if((j>0 && j<=12) || (j>=15 && j<27) ){
            tablero[i][j]=2;
        }
        else{
            tablero[i][j]=1;
        }
    }
    for (int i=2;i<5;i++){
        for (int j=0;j<28;j++){
            if(j==1 || j==6 || j==12 || j==15 || j==21 || j==26){
                tablero[i][j]=2;
            }
            else{
                tablero[i][j]=1;
            }
        }
    }
    for (int j=0;j<28;j++){
        i=5;
        if(j>=1 && j<=26){
            tablero[i][j]=2;
        }
        else{
            tablero[i][j]=1;
        }
    }
    for (int i=6;i<8;i++){
        for (int j=0;j<28;j++){
            if(j==1 || j==6 || j==9 || j==18 || j==21 || j==26){
                tablero[i][j]=2;
            }
            else{
                tablero[i][j]=1;
            }
        }
    }
    for (int j=0;j<28;j++){
        i=8;
        if((j>=1 && j<=6) || (j>=9 && j<=12) || (j>=15 && j<=18) || (j>=21 && j<=26)){
            tablero[i][j]=2;
        }
        else{
            tablero[i][j]=1;
        }
    }
    for (int j=0;j<28;j++){
        i=9;
        if(j==6 && j==21){
            tablero[i][j]=2;
        }
        else if((j>=0 && j<=5) || (j>=7 && j<=11) || j==13 || j==14 || (j>=16 && j<=20) || (j>=22 && j<=27)){
            tablero[i][j]=1;
        }
    }
    for (int j=0;j<28;j++){
        i=10;
        if(j==6 && j==21){
            tablero[i][j]=2;
        }
        else if((j==5) || (j>=7 && j<=11) || j==13 || j==14 || (j>=16 && j<=20) || (j==22)){
            tablero[i][j]=1;
        }
    }
    for (int i=11;i<13;i++){
        for (int j=0;j<28;j++){
            if(j==6 && j==21){
                tablero[i][j]=2;
            }
            else if((j==5) || (j>=7 && j<=8) || (j>=21 && j<=20) || (j==22)){
                tablero[i][j]=1;
            }
        }
    }
    for (int j=0;j<28;j++){
        i=13;
        if(j==6 && j==21){
            tablero[i][j]=2;
        }
        else if((j==5) || (j>=7 && j<=8) || (j>=21 && j<=20) || (j==22)){
            tablero[i][j]=1;
        }
    }
    tablero[16][6]=3;
    int matrizx=840/28;
    int matrizy=930/31;
    for (int i=0;i<31;i++){
        for (int j=0;j<28;j++){
            if (tablero[i][j]==1){
                int x = j * matrizx;
                int y = i * matrizy;

                rectItempared = new QGraphicsRectItem(x, y, matrizx, matrizy);
                rectItempared->setBrush(Qt::blue); // Establecer el color del cuadrado

                scene->addItem(rectItempared);
                paredes.push_back(rectItempared);
            }
            else if(tablero[i][j]==2){
                int x = j * matrizx;
                int y = i * matrizy;

                rectItemgalleta = new QGraphicsRectItem(x+7, y+7, matrizx/4, matrizy/4);
                rectItemgalleta->setBrush(Qt::yellow); // Establecer el color del cuadrado

                scene->addItem(rectItemgalleta);
                galletas.push_back(rectItemgalleta);
            }
            else if(tablero[i][j]==3){
                int x = j * matrizx;
                int y = i * matrizy;
                circle = new QGraphicsEllipseItem(x, y, matrizx, matrizy);
                circle->setRect(x, y, matrizx, matrizy);
                circle->setBrush(Qt::yellow);
                scene->addItem(circle);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animar()
{
    if(moverIx1)
    {
        circle->setPos(circle->x()-30,circle->y());
    }
    if(moverDx1)
    {
        circle->setPos(circle->x()+30,circle->y());
    }
    if(moverUy1)
    {
        circle->setPos(circle->x(),circle->y()-30);
    }
    if(moverDy1)
    {
        circle->setPos(circle->x(),circle->y()+30);
    }
    for (QGraphicsRectItem* azulItem : paredes) {
                if(circle->collidesWithItem(azulItem))
                {
                    if (circle->y()  <= azulItem->y() && moverUy1==true)
                    {
                        // La pared está arriba, se evita el movimiento hacia arriba
                        moverUy1 = false;
                    }
                    if (circle->y() >= azulItem->y() && moverDy1==true)
                    {
                        // La pared está abajo, se evita el movimiento hacia abajo
                        moverDy1 = false;
                    }
                    if (circle->x() <= azulItem->x() && moverIx1==true)
                    {
                        // La pared está a la izquierda, se evita el movimiento hacia la izquierda
                        moverIx1 = false;
                    }
                    if (circle->x() >= azulItem->x() && moverDx1==true)
                    {
                        // La pared está a la derecha, se evita el movimiento hacia la derecha
                        moverDx1 = false;
                    }
                }
    }
    for (QGraphicsRectItem* amarilloItem : galletas)
        if(circle->collidesWithItem(amarilloItem))
        {
            if(amarilloItem->isVisible()){
                amarilloItem->hide();
                emit aviso(9);
                //delete bola;
            }

        }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        moverIx1=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        moverDx1=true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        moverUy1=true;
    }
    else if(ev->key()==Qt::Key_Z)
    {
        moverDy1=true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        moverIx1=false;
    }
    else if(ev->key()==Qt::Key_S)
    {
        moverDx1=false;
    }
    else if(ev->key()==Qt::Key_W)
    {
        moverUy1=false;
    }
    else if(ev->key()==Qt::Key_Z)
    {
        moverDy1=false;
    }
}

    void MainWindow::aumentarPunt()
    {
        puntuacion += 5;
        ui->lcdNumber->display(puntuacion);
        std::cout<<puntuacion<<std::endl;
    }

