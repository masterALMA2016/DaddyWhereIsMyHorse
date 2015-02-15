#include "creationprojet.h"

CreationProjet::CreationProjet(QWidget * parent):QDialog(parent)
{
  setWindowTitle("Nouveau Projet");
  setMinimumSize(830,520);
  setMaximumSize(830, 520);

  QLabel *titre = new QLabel(this);
  titre->setText("Nouveau Projet");
  titre->setGeometry(300, 0, 350, 60);
  titre->setStyleSheet("font: 30pt");

  //Selection du film
  QLabel *film_source_titre = new QLabel(this);
  film_source_titre->setText("Film source");
  film_source_titre->setStyleSheet("font: 20pt");
  film_source_titre->setGeometry(20, 100, 150, 25);

  QLabel *emplacement_film = new QLabel(this);
  emplacement_film->setText("Emplacement: ");
  emplacement_film->setGeometry(20, 140, 100, 25);

  QLineEdit *chemin_video = new QLineEdit(this);
  chemin_video->setGeometry(130,140,200,25);

  QPushButton *parcourir = new QPushButton(this);
  parcourir->setText("Parcourir");
  parcourir->setGeometry(340, 140, 80, 25);


  //Projet

  QLabel *projet_titre = new QLabel(this);
  projet_titre->setText("Projet");
  projet_titre->setStyleSheet("font: 20pt");
  projet_titre->setGeometry(20, 200, 150, 35);

  QLabel *nom_projet_titre = new QLabel(this);
  nom_projet_titre->setText("Nom: ");
  nom_projet_titre->setGeometry(20, 240, 100, 25);

  QLineEdit *nom_projet = new QLineEdit(this);
  nom_projet->setGeometry(130,240,200,25);


  QLabel *emplacement_projet_titre = new QLabel(this);
  emplacement_projet_titre->setText("Emplacement: ");
  emplacement_projet_titre->setGeometry(20, 275, 100, 25);

  QLineEdit *chemin_projet = new QLineEdit(this);
  chemin_projet->setGeometry(130,275,200,25);

  QPushButton *parcourir_projet = new QPushButton(this);
  parcourir_projet->setText("Parcourir");
  parcourir_projet->setGeometry(340, 275, 80, 25);


  //Options

  QLabel *option_titre = new QLabel(this);
  option_titre->setText("Option");
  option_titre->setStyleSheet("font: 20pt");
  option_titre->setGeometry(20, 335, 150, 35);

  QLabel *frequence = new QLabel(this);
  frequence->setText("Fréquence: ");
  frequence->setGeometry(20, 375, 100, 25);

  QComboBox *choix_frequence = new QComboBox(this);
  choix_frequence->setGeometry(130, 375, 40, 25);
  choix_frequence->addItem(QString::fromUtf8("6"));
  choix_frequence->addItem(QString::fromUtf8("8"));
  choix_frequence->addItem(QString::fromUtf8("12"));
  choix_frequence->addItem(QString::fromUtf8("24"));

  QLabel *texte_frequence = new QLabel(this);
  texte_frequence->setText("images par seconde");
  texte_frequence->setGeometry(180, 375, 200, 25);


  //boutons
  QPushButton *annuler = new QPushButton(this);
  annuler->setText(QString::fromUtf8("Annuler"));
  annuler->setGeometry(10, 470, 100, 40);
  connect(annuler, SIGNAL(clicked()), this, SLOT(close()));

  QPushButton *creer = new QPushButton(this);
  creer->setText(QString::fromUtf8("Creer"));
  creer->setGeometry(720, 470, 100, 40);
  connect(creer, SIGNAL(clicked()), this, SLOT(envoyer_informations()));



}

CreationProjet::~CreationProjet()
{

}

void CreationProjet::envoyer_informations(){
    emit information_projet("ii", "hh", "kk", "mm");
    close();
}
