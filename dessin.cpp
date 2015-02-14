#include "dessin.h"
#include <QCursor>
#include <QMouseEvent>
#include <iostream>

Dessin::Dessin(QWidget * parent):QLabel(parent), dessin(200, 200), crayon(Qt::blue)
{
    dessin.fill(Qt::transparent);
    crayon.setCapStyle(Qt::RoundCap);
    setPixmap(dessin);
    trace = false;
}

Dessin::~Dessin()
{

}

void Dessin::mousePressEvent ( QMouseEvent * event ){
    QPainter paint(&dessin);
    paint.setPen(crayon);
    x = event->x();
    y = event->y();
    trace = true;
    paint.drawPoint(event->x(), event->y());
    setPixmap(dessin);
}

void Dessin::mouseMoveEvent( QMouseEvent * event ){

    QPainter paint(&dessin);
    paint.setPen(crayon);
    if(trace){
        paint.drawLine(x, y, event->x(), event->y());
        x = event->x();
        y=event->y();
        setPixmap(dessin);
    }
}

void Dessin::mouseReleaseEvent(QMouseEvent *event){
    trace = false;
}

void Dessin::set_color(QColor couleur){
    crayon.setColor(couleur);
}
