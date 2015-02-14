#include "accueil.h"
#include <QVBoxLayout>
#include <iostream>
#include "projet.h"


Accueil::Accueil(QWidget *parent):QMainWindow(parent)
{
    longueur_fenetre = 1245;
    largeur_fenetre = 883;

    this->setWindowTitle("Accueil");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    message_accueil = new QLabel(this);
    message_accueil->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    message_accueil->setText("Pas de projet ouvert");
    message_accueil->setGeometry(QRect(500, 350, 150, 20));

    nouveau_projet = new QPushButton("Nouveau projet", this);
    nouveau_projet->setGeometry(500, 400, 150, 50);

    charger_projet = new QPushButton("Charger projet", this);
    charger_projet->setGeometry(500, 450, 150, 50);

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(creer_projet()));
    connect(charger_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));
}

Accueil::~Accueil()
{
}

void Accueil::creer_projet(){

    delete(charger_projet);
    delete(nouveau_projet);
    delete(message_accueil);
    Projet *projet = new Projet(longueur_fenetre, largeur_fenetre);
    projet->show();
    this->close();

}

void Accueil::ouvrir_projet(){

}
