#include "creationprojet.h"

CreationProjet::CreationProjet(QWidget * parent):QDialog(parent)
{
  setWindowTitle("Nouveau Projet");
  setMinimumSize(830,520);
  setMaximumSize(830, 520);

  QPushButton *annuler = new QPushButton(this);
  annuler->setText(QString::fromUtf8("Annuler"));
  annuler->setGeometry(0, 480, 100, 40);
  connect(annuler, SIGNAL(clicked()), this, SLOT(close()));

  QPushButton *creer = new QPushButton(this);
  creer->setText(QString::fromUtf8("Creer"));
  creer->setGeometry(730, 480, 100, 40);
  connect(creer, SIGNAL(clicked()), this, SLOT(envoyer_informations()));

}

CreationProjet::~CreationProjet()
{

}

void CreationProjet::envoyer_informations(){
    emit information_projet("ii", "hh", "kk", "mm");
    close();
}
