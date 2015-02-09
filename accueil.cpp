#include "accueil.h"
#include <QVBoxLayout>

Accueil::Accueil(QWidget *parent):QMainWindow(parent)
{
    longueur = 1050;
    largeur = 740;
    this->setWindowTitle("Accueil");
    this->setMinimumSize(longueur,largeur);
    this->setMaximumSize(longueur,largeur);

    label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Pas de projet ouvert");
    label->setGeometry(QRect(500, 350, 150, 20));
    QLabel label1;
    label1.setText("jjj");
    QLabel label2;
    label2.setText("cccc");
    QLabel label3;
    label3.setText("aaaaa");
    QVBoxLayout test;
    test.addWidget(&label3);
    test.addWidget(&label2);
    test.addWidget(&label1);
    this->setLayout(&test);
    nouveau_projet = new QPushButton("Nouveau projet", this);
    nouveau_projet->setGeometry(500, 400, 150, 50);

    charger_projet = new QPushButton("Charger projet", this);
    charger_projet->setGeometry(500, 450, 150, 50);

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));
}

Accueil::~Accueil()
{
}

void Accueil::ouvrir_projet(){

    delete(charger_projet);
    delete(nouveau_projet);
    delete(label);

}

