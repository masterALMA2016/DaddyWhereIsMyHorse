#include "imageclickable.h"
#include <iostream>
ImageClickable::ImageClickable(std::string s, int index, QWidget *parent):QLabel(parent)
{
    this->index = index;
    path=s;
    QPixmap p( s.c_str() );
    p = p.scaledToWidth(160,  Qt::FastTransformation);
    std::string str ="border-image: url("+path+")";
    //this->setGeometry(this->x(), this->y(), p.width(), p.height());
    this->setMinimumSize(p.width(), p.height());
    this->setMaximumSize(p.width(), p.height());
    this->setStyleSheet(str.c_str());
    //this->setPixmap(p);
}

ImageClickable::~ImageClickable()
{
}

void ImageClickable::mousePressEvent ( QMouseEvent * event ){
    emit clicked(this->path, this->path2, this->index);
}

std::string ImageClickable::get_path(){
    return path;
}

std::string ImageClickable::get_path2(){
    return path2;
}

void ImageClickable::changer_image(QString img){
    QPixmap temp(img);
    temp.scaledToWidth(160,  Qt::FastTransformation);
    setPixmap(temp);

}

void ImageClickable::set_path2(std::string p2){
    path2 = p2;
}
