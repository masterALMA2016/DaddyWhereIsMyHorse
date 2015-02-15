#include "accueil.h"
#include <QVBoxLayout>
#include <iostream>
#include "projet.h"
#include <QDir>
#include <creationprojet.h>
Accueil::Accueil(QWidget *parent):QMainWindow(parent)
{
    longueur_fenetre = 1245;
    largeur_fenetre = 883;

    this->setWindowTitle("Accueil");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    message_accueil = new QLabel(this);
    message_accueil->setText("Pas de projet ouvert");
    message_accueil->setStyleSheet("font: 40pt");
    message_accueil->setGeometry(QRect(420, 300, 480, 80));

    QPixmap image("../DaddyWhereIsMyHorse/lecture.png");
    image=image.scaledToWidth(20);
    QIcon icone_bouton(image);

    nouveau_projet = new QPushButton("Nouveau projet", this);
    nouveau_projet->setGeometry(530, 400, 250, 50);
    nouveau_projet->setStyleSheet("font: 15pt");
    nouveau_projet->setIcon(icone_bouton);
    nouveau_projet->setIconSize(image.rect().size());

    charger_projet = new QPushButton("Charger projet", this);
    charger_projet->setGeometry(530, 500, 250, 50);
    charger_projet->setStyleSheet("font: 15pt");
    charger_projet->setIcon(icone_bouton);
    charger_projet->setIconSize(image.rect().size());

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(creer_projet()));
    connect(charger_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));

}

Accueil::~Accueil()
{
}

void Accueil::creer_projet(){

    CreationProjet *cp = new CreationProjet(this);
    connect(cp, SIGNAL(information_projet(std::string,std::string,std::string,std::string)), this, SLOT(recuperer_informations(std::string, std::string , std::string , std::string )));
    cp->show();
}

void Accueil::ouvrir_projet(){

}

void Accueil::recuperer_informations(std::string nom_projet, std::string chemin_projet, std::string chemin_video, std::string frequence){
    delete(charger_projet);
    delete(nouveau_projet);
    delete(message_accueil);
    Projet *projet = new Projet(longueur_fenetre, largeur_fenetre);
    projet->show();
    this->close();
}
