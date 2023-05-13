#include "pacman.h"

pacman::pacman()
{

}

void pacman::dimensiones(int x,int y,int rectangleWidth,int rectangleHeight){
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(x, y, rectangleWidth, rectangleHeight);
    circle->setRect(x, y, rectangleWidth, rectangleHeight);
    circle->setBrush(Qt::yellow);
}


