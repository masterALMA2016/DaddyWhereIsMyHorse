#include "accueil.h"
#include <QVBoxLayout>
#include <iostream>
#include "projet.h"
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

    QPalette couleur_texte;
    couleur_texte.setColor(QPalette::WindowText, Qt::red);

    probleme_ouverture_projet = new QLabel(this);
    probleme_ouverture_projet->setText(QString::fromUtf8("Ce répertoire ne correspond pas à un projet DaddyWhereIsMyHorse"));
    probleme_ouverture_projet->setPalette(couleur_texte);
    probleme_ouverture_projet->setVisible(false);
    probleme_ouverture_projet->setGeometry(450, 570, 500, 25);

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(creer_projet()));
    connect(charger_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));
}

Accueil::~Accueil()
{
    delete(charger_projet);
    delete(nouveau_projet);
    delete(message_accueil);
}

void Accueil::creer_projet(){

    CreationProjet *cp = new CreationProjet(this);
    connect(cp, SIGNAL(information_projet(QString, QString)), this, SLOT(recuperer_informations(QString, QString )));
    cp->show();
}

void Accueil::ouvrir_projet(){

    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directoriy"), QDir::home().path(), QFileDialog::ShowDirsOnly);
    QDir dir(path+"/images_video");
    if(!dir.exists()){
        probleme_ouverture_projet->setVisible(true);
    }
    else{
        Projet *projet = new Projet(longueur_fenetre, largeur_fenetre, 0, path);
        projet->show();
        this->close();
    }
}

void Accueil::recuperer_informations(QString chemin_projet, QString frequence){

    Projet *projet = new Projet(longueur_fenetre, largeur_fenetre, frequence, chemin_projet);
    projet->show();
    this->close();
}
