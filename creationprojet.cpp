#include "creationprojet.h"
#include <iostream>
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

  chemin_video = new QLineEdit(this);
  chemin_video->setGeometry(130,140,200,25);

  QPushButton *parcourir = new QPushButton(this);
  parcourir->setText("Parcourir");
  parcourir->setGeometry(340, 140, 80, 25);

  probleme_chemin_video = new QLabel(this);
  probleme_chemin_video->setText("Ce répertoire n'existe pas");
  probleme_chemin_video->setVisible(false);
  probleme_chemin_video->setGeometry(430,140,170,25);
  QPalette couleur_texte;
  couleur_texte.setColor(QPalette::WindowText, Qt::red);
  probleme_chemin_video->setPalette(couleur_texte);

  //Projet

  QDir home = QDir::home();
  QString dossier("sans nom");
  QDir nouveau_dossier(home.path() + "/sans nom");
  bool existe = nouveau_dossier.exists();
  int i = 1;
  while(existe){
      nouveau_dossier.setPath(nouveau_dossier.path() + QString::number(i));
      existe = nouveau_dossier.exists();
      if(!existe){
          dossier += QString::number(i);
      }
      i++;
  }


  QLabel *projet_titre = new QLabel(this);
  projet_titre->setText("Projet");
  projet_titre->setStyleSheet("font: 20pt");
  projet_titre->setGeometry(20, 200, 150, 35);

  QLabel *nom_projet_titre = new QLabel(this);
  nom_projet_titre->setText("Nom: ");
  nom_projet_titre->setGeometry(20, 240, 100, 25);

  nom_projet = new QLineEdit(this);
  nom_projet->setGeometry(130,240,200,25);
  nom_projet->setText(dossier);

  probleme_nom_projet = new QLabel(this);
  probleme_nom_projet->setText("Ce répertoire existe déjà");
  probleme_nom_projet->setVisible(false);
  probleme_nom_projet->setGeometry(340,240,170,25);
  couleur_texte.setColor(QPalette::WindowText, Qt::red);
  probleme_nom_projet->setPalette(couleur_texte);

  QLabel *emplacement_projet_titre = new QLabel(this);
  emplacement_projet_titre->setText("Emplacement: ");
  emplacement_projet_titre->setGeometry(20, 275, 100, 25);

  chemin_projet = new QLineEdit(this);
  chemin_projet->setGeometry(130,275,200,25);
  chemin_projet->setText(home.path());

  QPushButton *parcourir_projet = new QPushButton(this);
  parcourir_projet->setText("Parcourir");
  parcourir_projet->setGeometry(340, 275, 80, 25);

  probleme_chemin_projet = new QLabel(this);
  probleme_chemin_projet->setText("Ce répertoire n'existe pas");
  probleme_chemin_projet->setVisible(false);
  probleme_chemin_projet->setGeometry(430,275,170,25);
  couleur_texte.setColor(QPalette::WindowText, Qt::red);
  probleme_chemin_projet->setPalette(couleur_texte);

  //Options

  QLabel *option_titre = new QLabel(this);
  option_titre->setText("Option");
  option_titre->setStyleSheet("font: 20pt");
  option_titre->setGeometry(20, 335, 150, 35);

  QLabel *frequence = new QLabel(this);
  frequence->setText("Fréquence: ");
  frequence->setGeometry(20, 375, 100, 25);

  choix_frequence = new QComboBox(this);
  choix_frequence->setGeometry(130, 375, 45, 25);
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

  connect(parcourir_projet, SIGNAL(clicked()), this, SLOT(parcourir_dossier()));
  connect(parcourir, SIGNAL(clicked()), this, SLOT(parcourir_video()));

}

CreationProjet::~CreationProjet()
{
    delete(nom_projet);
    delete(chemin_video);
    delete(choix_frequence);
    delete(chemin_projet);
    delete(probleme_chemin_projet);
    delete(probleme_nom_projet);
    delete(probleme_chemin_video);
}

void CreationProjet::envoyer_informations(){

    QFile video_dir(chemin_video->text());
    bool chemin_video_existe = video_dir.exists() && !chemin_video->text().isEmpty() ;

    if(!chemin_video_existe){
        probleme_chemin_video->setVisible(true);
    }
    else{
        probleme_chemin_video->setVisible(false);
    }

    //si le nom du dossier du projet a un espace ca ne fonctionne pas
    nom_projet->setText(nom_projet->text().replace(" ", "_"));
    QDir nom_projet_dir(chemin_projet->text() + "/" + nom_projet->text());
    bool nom_projet_existe = !nom_projet_dir.exists() && !nom_projet->text().isEmpty();

    if(!nom_projet_existe){
        probleme_nom_projet->setVisible(true);
    }
    else{
        probleme_nom_projet->setVisible(false);
    }

    QDir chemin_projet_dir(chemin_projet->text());
    bool chemin_projet_existe = chemin_projet_dir.exists() && !chemin_projet->text().isEmpty();

    if(!chemin_projet_existe){
        probleme_chemin_projet->setVisible(true);
    }
    else{
        probleme_chemin_projet->setVisible(false);
    }


    if(chemin_video_existe && chemin_projet_existe && nom_projet_existe){
        QDir dir_projet(chemin_projet->text());
        dir_projet.mkdir(nom_projet->text());
        dir_projet.cd(nom_projet->text());
        QString nouveau_projet = dir_projet.path();

        dir_projet.mkdir("images_video");
        dir_projet.mkdir("dessins");
        dir_projet.mkdir("calque");
        dir_projet.mkdir("videos");
        dir_projet.cd("images_video");
        std::string str = "ffmpeg -i " + chemin_video->text().toStdString()+" -r " + choix_frequence->currentText().toStdString() + " " + dir_projet.path().toStdString() + "/image%03d.png";
        system(str.c_str());
        QFile configuration;
        configuration.setFileName("dwimh.conf");
        configuration.open(QIODevice::WriteOnly);
        configuration.write(choix_frequence->currentText().toStdString().c_str());
        configuration.write("\n" );
        configuration.write(QString::number(5).toStdString().c_str());
        configuration.write("\n" );
        configuration.write(QString::number(1).toStdString().c_str());
        configuration.write("\n" );
        configuration.write(QString::number(10).toStdString().c_str());
        configuration.write("\n" );
        configuration.write(QString::number(0).toStdString().c_str());
        nouveau_projet+="/dwimh.conf";
        configuration.copy(nouveau_projet );
        configuration.remove();
        configuration.close();
        emit information_projet(nom_projet_dir.path(), choix_frequence->currentText());
        close();
    }
}

void CreationProjet::parcourir_dossier(){
    chemin_projet->setText(QFileDialog::getExistingDirectory(this, tr("Open Directoriy"), QDir::home().path(), QFileDialog::ShowDirsOnly));
}

void CreationProjet::parcourir_video(){
    chemin_video->setText(QFileDialog::getOpenFileName(this, tr("Open File"), QDir::home().path(), tr("Videos (*.avi *.mpeg *.mp4)")));
}
