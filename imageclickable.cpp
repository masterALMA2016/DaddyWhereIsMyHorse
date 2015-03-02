#include "imageclickable.h"
#include <iostream>
ImageClickable::ImageClickable(std::string nouveau_path_image_film, QWidget *parent):QLabel(parent)
{
    path_image_film = nouveau_path_image_film;
    path_dessin = "";
    QPixmap image_film_temp(nouveau_path_image_film.c_str());
    image_film_temp = image_film_temp.scaledToWidth(180,  Qt::FastTransformation);
    std::string option_image_de_fond ="border-image: url(" + path_image_film + ")";

    this->setMinimumSize(image_film_temp.width(), image_film_temp.height());
    this->setMaximumSize(image_film_temp.width(), image_film_temp.height());
    this->setStyleSheet(option_image_de_fond.c_str());
}

ImageClickable::~ImageClickable()
{
}

std::string ImageClickable::get_path_image_film(){
    return path_image_film;
}

std::string ImageClickable::get_path_dessin(){
    return path_dessin;
}

void ImageClickable::changer_image(QString nouveau_path_image){
    QPixmap temp(nouveau_path_image);
    path_dessin = nouveau_path_image.toStdString();
    temp = temp.scaledToWidth(180,  Qt::FastTransformation);
    setPixmap(temp);
}

void ImageClickable::set_path_dessin(std::string nouveau_path_dessin){
    path_dessin = nouveau_path_dessin;
}

void ImageClickable::set_affichage_image(bool choix){
    if(choix){
        this->setStyleSheet("background-color: transparent");
    }
    else{
        std::string option_image_de_fond ="border-image: url(" + path_image_film + ")";
        this->setStyleSheet(option_image_de_fond.c_str());
    }
}

void ImageClickable::set_affichage_dessin(bool choix){
    if(!choix){
        setPixmap(QPixmap());
    }
    else if(!path_dessin.empty()){
        QPixmap temp(path_dessin.c_str());
        temp = temp.scaledToWidth(180,  Qt::FastTransformation);
        setPixmap(temp);
    }
}
