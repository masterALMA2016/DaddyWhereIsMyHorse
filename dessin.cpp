#include "dessin.h"
#include <QCursor>
#include <QMouseEvent>
#include <iostream>

Dessin::Dessin(QWidget * parent):QLabel(parent), dessin(200, 200)
{
  //  dessin.fill(Qt::transparent);
    setPixmap(dessin);
    trace = false;
}

Dessin::~Dessin()
{

}

void Dessin::mousePressEvent ( QMouseEvent * event ){
    QPainter paint(&dessin);
    QPen b(Qt::blue);
    b.setWidthF(20.0);
    b.setCapStyle(Qt::RoundCap);
    paint.setPen(b);
    x = event->x();
    y=event->y();
    trace = true;
    paint.drawPoint(event->x(), event->y());
    bool t = dessin.save("test", "PNG");
    setPixmap(dessin);
    std::cout<<t<<std::endl;
    emit clicked(event->y(), event->x());
}

void Dessin::mouseMoveEvent( QMouseEvent * event ){
    QPainter paint(&dessin);
    QPen b(Qt::blue);
    b.setWidthF(20.0);
    b.setCapStyle(Qt::RoundCap);
    paint.setPen(b);
    if(!trace){

    paint.drawPoint(event->x(), event->y());
    bool t = dessin.save("test", "PNG");
    setPixmap(dessin);
    std::cout<<t<<std::endl;
    emit clicked(event->y(), event->x());
    trace =true;
    }
    else{
        paint.drawLine(x, y, event->x(), event->y());
        x = event->x();
        y=event->y();
        setPixmap(dessin);

    }
}

void Dessin::mouseReleaseEvent(QMouseEvent *event){
    trace = false;
}
