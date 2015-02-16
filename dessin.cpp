#include "dessin.h"
#include <QCursor>
#include <QMouseEvent>
#include <iostream>
Dessin::Dessin(int longueur, int largeur, QWidget * parent):QLabel(parent), dessin(longueur, largeur), crayon(Qt::blue)
{
    dessin.fill(Qt::transparent);
    setStyleSheet("background: transparent");
    crayon.setCapStyle(Qt::RoundCap);
    setPixmap(dessin);
    trace = false;
    utiliser_crayon = true;
}

Dessin::~Dessin()
{

}

void Dessin::mousePressEvent ( QMouseEvent * event ){
        QPainter paint(&dessin);
        if(!utiliser_crayon){
            crayon.setColor(Qt::transparent);
            paint.setCompositionMode(QPainter::CompositionMode_SourceIn);
        }
        paint.setPen(crayon);
        x = event->x();
        y = event->y();
        trace = true;
        paint.drawPoint(event->x(), event->y());
        setPixmap(dessin);

}

void Dessin::mouseMoveEvent( QMouseEvent * event ){

    QPainter paint(&dessin);
    if(!utiliser_crayon){
        crayon.setColor(Qt::transparent);
        paint.setCompositionMode(QPainter::CompositionMode_SourceIn);

    }
    paint.setPen(crayon);
    paint.drawLine(x, y, event->x(), event->y());
    paint.end();
    x = event->x();
    y = event->y();
    setPixmap(dessin);
}

void Dessin::mouseReleaseEvent(){
    trace = false;
}

void Dessin::set_color(QColor couleur){
    crayon.setColor(couleur);
}

QColor Dessin::get_color(){
    return crayon.color();
}

void Dessin::changer_taille_crayon(int i){
    crayon.setWidth(i);
}

void Dessin::set_t(bool choix){
    utiliser_crayon=choix;
}

void Dessin::save(QString chemin){
    dessin.save(chemin, "PNG");
}

QPixmap Dessin::get_image(){
    return dessin;
}
