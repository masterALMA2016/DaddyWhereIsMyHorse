#include "dessin.h"
#include <QCursor>
#include <QMouseEvent>
#include <iostream>
Dessin::Dessin(int longueur, int largeur, QWidget * parent):QLabel(parent), dessin(longueur, largeur), crayon(Qt::blue)
{

    dessin.fill(Qt::transparent);
    crayon.setCapStyle(Qt::RoundCap);

    tracer_ligne = false;
    utiliser_crayon = true;

    setStyleSheet("background: transparent");
    setPixmap(dessin);
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
        tracer_ligne = true;
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
    tracer_ligne = false;
}

void Dessin::set_color(QColor couleur){
    crayon.setColor(couleur);
}

QColor Dessin::get_color(){
    return crayon.color();
}

void Dessin::changer_taille_crayon(int nouvelle_taille){
    crayon.setWidth(nouvelle_taille);
}

void Dessin::set_utiliser_crayon(bool choix){
    utiliser_crayon = choix;
}

void Dessin::save(QString chemin){
    dessin.save(chemin, "PNG");
}

QPixmap Dessin::get_image(){
    return dessin;
}

void Dessin::set_dessin(QPixmap image){
    dessin = image;
    setPixmap(dessin);
}
