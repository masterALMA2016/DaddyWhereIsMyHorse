#include "erreur.h"

Erreur::Erreur(QWidget *parent):QDialog(parent)
{
    setMinimumSize(300, 120);
    setMaximumSize(300, 120);
    setWindowTitle("Your horse is not here");

    QLabel *message_erreur = new QLabel(this);
    message_erreur->setText("Ce dossier ne contient aucun projet\nDaddyWhereIsMyHorse");
    message_erreur->setGeometry(20, 0, 250, 50);
    QPalette couleur_texte;
    couleur_texte.setColor(QPalette::WindowText, Qt::red);
    message_erreur->setPalette(couleur_texte);

    QPushButton *fermer = new QPushButton(this);
    fermer->setText("Fermer");
    fermer->setGeometry(100, 60, 100, 40);
    connect(fermer, SIGNAL(clicked()), this, SLOT(close()));
}

Erreur::~Erreur()
{

}

