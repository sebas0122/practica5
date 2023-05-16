#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette = ui->graphicsView->palette();
    palette.setColor(QPalette::Base, Qt::black);
    ui->graphicsView->setPalette(palette);

    timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(animar()));
    connect(this,SIGNAL(aviso(int)),this,SLOT(aumentarPunt()));

    timer->start(90);

    scene=new QGraphicsScene(0,0,930,840);
    ui->graphicsView->setScene(scene);

    int i=0;
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
    for (int j=0;j<28;j++){
        i=14;
        tablero[i][j]=1;
    }

    tablero[13][6]=3;
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
                circle = new QGraphicsEllipseItem(x, y, matrizx-10, matrizy-10);
                circle->setRect(x+5, y+5, matrizx-10, matrizy-10);
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
    for (QGraphicsRectItem* azulItem : paredes) {
            if (circle->collidesWithItem(azulItem)) {
                if ((lastPress == 3)) {
                    // La pared está arriba, se evita el movimiento hacia arriba
                    circle->setPos(circle->x(),circle->y()+5);
                    moverUy1 = false;
                }
                if ((lastPress == 4) ) {
                    // La pared está abajo, se evita el movimiento hacia abajo
                    circle->setPos(circle->x(),circle->y()-5);
                    moverDy1 = false;
                }
                if ((lastPress== 1)) {
                    // La pared está a la izquierda, se evita el movimiento hacia la izquierda
                    circle->setPos(circle->x()+5,circle->y());
                    moverIx1 = false;
                }
                if ((lastPress == 2)) {
                    // La pared está a la derecha, se evita el movimiento hacia la derecha
                    circle->setPos(circle->x()-5,circle->y());
                    moverDx1 = false;
                }
            }
        }
        if(moverIx1)
        {
            circle->setPos(circle->x()-5,circle->y());
        }
        else if(moverDx1)
        {
            circle->setPos(circle->x()+5,circle->y());
        }
        else if(moverUy1)
        {
            circle->setPos(circle->x(),circle->y()-5);
        }
        else if(moverDy1)
        {
            circle->setPos(circle->x(),circle->y()+5);
        }
    for (QGraphicsRectItem* amarilloItem : galletas){
       if(circle->collidesWithItem(amarilloItem))
        {
            if(amarilloItem->isVisible()){
                amarilloItem->hide();
                emit aviso(10);
                //delete bola;
            }

        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        lastPress=1;
        moverIx1=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        lastPress=2;
        moverDx1 = true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        lastPress=3;
       moverUy1=true;
    }
    else if(ev->key()==Qt::Key_Z)
    {
        lastPress=4;
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

