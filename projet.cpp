#include "projet.h"
#include <iostream>
#include <QEvent>
#include <QDockWidget>
#include <QPainter>
Projet::Projet(int x, int y, QWidget *parent):QMainWindow(parent)
{
    longueur=x;
    largeur=y;



    barre_menu = new QMenuBar(this);
    setMenuBar(barre_menu);
    barre_menu->setVisible(true);
    QMenu *fichier = new QMenu("fichier");
    barre_menu->addMenu(fichier);
    QAction *ac = new QAction(this);
    ac->setText(QString::fromUtf8("fermer"));
    ac->setShortcut(QKeySequence("CTRL+Q"));

connect(ac, SIGNAL(triggered()), this, SLOT(close()));
    fichier->addAction(ac);

    d = new Dessin(this);
    d->setGeometry(500, 500,200,200);


    QPushButton *couleur = new QPushButton(this);
    couleur->setObjectName(QString::fromUtf8("couleur"));
    couleur->setGeometry(longueur-100, barre_menu->geometry().height() ,40 ,30);
    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur,largeur);
    this->setMaximumSize(longueur,largeur);

    QPixmap p( "/home/Soge/Images/Wallpapers/game_of_thrones_016.jpg" );
    p= p.scaledToWidth(160,  Qt::FastTransformation);

    std::string s2="/home/Soge/Images/Wallpapers/game_of_thrones_016.jpg";
    label1=new ImageClickable(s2);
   // label1->setPixmap( p );

    ImageClickable *label2=new ImageClickable(s2);

    label2->setPixmap(p);
    ImageClickable *label3=new ImageClickable(s2);
    label3->setPixmap( p);
    ImageClickable *label4=new ImageClickable(s2);
    label4->setPixmap( p );
    ImageClickable *label5=new ImageClickable(s2);
    label5->setPixmap( p );
    ImageClickable *label6=new ImageClickable(s2);
    label6->setPixmap( p );
    ImageClickable *label7=new ImageClickable(s2);
    label7->setPixmap( p );
    ImageClickable *label8=new ImageClickable(s2);
    label8->setPixmap( p );
    ImageClickable *label9=new ImageClickable(s2);
    label9->setPixmap( p );
    ImageClickable *label10=new ImageClickable(s2);
    label10->setPixmap( p );
    ImageClickable *label11=new ImageClickable(s2);
    label11->setPixmap( p );
    ImageClickable *label12=new ImageClickable(s2);
    label12->setPixmap( p );

    QScrollArea *scrollarea = new QScrollArea(this);

    QVBoxLayout *test = new QVBoxLayout();
    test->addWidget(label3);
    test->addWidget(label2);
    test->addWidget(label4);
    test->addWidget(label5);
    test->addWidget(label6);
    test->addWidget(label7);
    test->addWidget(label8);
    test->addWidget(label9);
    test->addWidget(label11);
    test->addWidget(label12);
    test->addWidget(label10);
    test->addWidget(label1);
    ma = new QWidget(this);
    ma->setLayout(test);
    scrollarea->setWidget(ma);
    scrollarea->setGeometry(0, barre_menu->geometry().y()+barre_menu->height(), 205, largeur-barre_menu->geometry().height());

    connect(label1, SIGNAL(clicked(std::string)), this, SLOT(test(std::string)));
}

Projet::~Projet()
{

}



void Projet::dessin(int x, int y){
std::cout<<"fgvhjvhkbmkhbl"<<std::endl;
}
