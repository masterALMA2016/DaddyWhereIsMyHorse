#include "dessin.h"
#include <QCursor>
#include <QMouseEvent>
#include <iostream>
Dessin::Dessin(int longueur, int largeur, QWidget * parent):QLabel(parent), dessin(longueur, largeur), crayon(Qt::blue)
{

    sauvegarder = false;
    dessin.fill(Qt::transparent);
    crayon.setCapStyle(Qt::RoundCap);

    tracer_ligne = false;
    utiliser_crayon = true;

    setStyleSheet("background: transparent");
    setPixmap(dessin);

    path_souris = ":/rsc/img/crayon.png";
    QPixmap crayon_souris(path_souris.c_str());
    image_souris = crayon_souris.scaledToWidth(15);
    curseur = QCursor(image_souris, 0, 15);
    setCursor(curseur);
}

Dessin::~Dessin()
{

}

void Dessin::mousePressEvent ( QMouseEvent * event ){
        sauvegarder = true;

        ancien = dessin;

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
    QPixmap crayon_souris(path_souris.c_str());

    image_souris = crayon_souris.scaledToWidth(nouvelle_taille*3.75);
    curseur = QCursor(image_souris, 0, nouvelle_taille*3.75);
    setCursor(curseur);

    crayon.setWidth(nouvelle_taille);
}

void Dessin::set_utiliser_crayon(bool choix){
    utiliser_crayon = choix;
    if(choix){
        path_souris = ":/rsc/img/crayon.png";
    }
    else{
        path_souris = ":/rsc/img/gomme.png";
    }

    QPixmap crayon_souris(path_souris.c_str());

    image_souris = crayon_souris.scaledToWidth(image_souris.width());
    curseur = QCursor(image_souris, 0, image_souris.width());
    setCursor(curseur);
}

void Dessin::save(QString dossier, QString chemin_dessin, QString chemin_calque, std::string chemin_image_film, std::string chemin_dessin_film){
    sauvegarder = false;

    QPixmap temp(dessin.width(), dessin.height());
    temp.fill(Qt::white);
    QPainter paint(&temp);
    paint.drawPixmap(temp.rect(), dessin, dessin.rect());
    temp.save(chemin_dessin, "PNG");
    dessin.save(chemin_calque, "PNG");

    QPixmap temp2(chemin_image_film.c_str());
    QPainter paint2(&temp2);
    paint2.drawPixmap(temp.rect(), dessin, dessin.rect());
    temp2.save(chemin_dessin_film.c_str(), "PNG");
}

QPixmap Dessin::get_image(){
    return dessin;
}

void Dessin::set_dessin(QPixmap image){
    dessin = image;
    setPixmap(dessin);
}

void Dessin::undo(QString dossier){
    sauvegarder = true;
    if(!ancien.isNull()){
        dessin = ancien;
        setPixmap(dessin);
        ancien = QPixmap();
    }

}

bool Dessin::to_save(){
    return sauvegarder;
}
