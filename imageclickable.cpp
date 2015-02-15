#include "imageclickable.h"
#include <iostream>
ImageClickable::ImageClickable(std::string s, QWidget *parent):QLabel(parent)
{
    path=s;
    QPixmap p( s.c_str() );
    p = p.scaledToWidth(160,  Qt::FastTransformation);
    this->setPixmap(p);
}

ImageClickable::~ImageClickable()
{
}

void ImageClickable::mousePressEvent ( QMouseEvent * event ){
    emit clicked(this->path);
}


