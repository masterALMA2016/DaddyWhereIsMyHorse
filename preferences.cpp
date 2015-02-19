#include "preferences.h"

Preferences::Preferences(int new_nb_pelures_doignons, int new_frequences_pelures_doignons, int new_previsualisation, bool new_image_fond, QWidget *parent): QDialog(parent)
{
    setWindowTitle(QString::fromUtf8("Préférences"));
    setMinimumSize(500,180);
    setMaximumSize(500, 180);

    QLabel *nb_pelure_doignons_texte = new QLabel(this);
    nb_pelure_doignons_texte->setText("Nombre de pelures d'oignons: ");
    nb_pelure_doignons_texte->setStyleSheet("font: 14pt");
    nb_pelure_doignons_texte->setGeometry(10, 10, 250, 25);

    nb_pelure_doignons = new QLineEdit(this);
    nb_pelure_doignons->setGeometry(270,10,35,25);
    nb_pelure_doignons->setMaxLength(2);
    nb_pelure_doignons->setText(QString::number(new_nb_pelures_doignons));

    QLabel *frequence_pelures_doignons_texte = new QLabel(this);
    frequence_pelures_doignons_texte->setText(QString::fromUtf8("Fréquence pelures d'oignons: 1/"));
    frequence_pelures_doignons_texte->setStyleSheet("font: 14pt");
    frequence_pelures_doignons_texte->setGeometry(10, 45, 250, 25);

    choix_frequence_pelures_doignons = new QComboBox(this);
    choix_frequence_pelures_doignons->setGeometry(270, 45, 55, 25);
    choix_frequence_pelures_doignons->addItem(QString::fromUtf8("1"));
    choix_frequence_pelures_doignons->addItem(QString::fromUtf8("2"));
    choix_frequence_pelures_doignons->addItem(QString::fromUtf8("3"));
    choix_frequence_pelures_doignons->addItem(QString::fromUtf8("4"));
    choix_frequence_pelures_doignons->setCurrentText(QString::number(new_frequences_pelures_doignons));

    QLabel *previsualisation_rapide_texte1 = new QLabel(this);
    previsualisation_rapide_texte1->setText(QString::fromUtf8("Prévisualisation rapide: les "));
    previsualisation_rapide_texte1->setStyleSheet("font: 14pt");
    previsualisation_rapide_texte1->setGeometry(10, 75, 250, 25);

    previsualisation_rapide = new QLineEdit(this);
    previsualisation_rapide->setGeometry(270,75,55,25);
    previsualisation_rapide->setText(QString::number(new_previsualisation));

    QLabel *previsualisation_rapide_texte2 = new QLabel(this);
    previsualisation_rapide_texte2->setText(QString::fromUtf8("dernières images"));
    previsualisation_rapide_texte2->setStyleSheet("font: 14pt");
    previsualisation_rapide_texte2->setGeometry(330, 75, 150, 25);

    image_de_fond = new QCheckBox(this);
    image_de_fond->setText("Afficher image de fond dans la vidéo");
    image_de_fond->setStyleSheet("font: 14pt");
    image_de_fond->setGeometry(10, 105, 326, 25);
    image_de_fond->setLayoutDirection(Qt::RightToLeft);
    image_de_fond->setChecked(new_image_fond);


    QPushButton *fermer = new QPushButton(this);
    fermer->setText(QString::fromUtf8("Fermer"));
    fermer->setGeometry(400, 140, 100, 40);
    connect(fermer, SIGNAL(clicked()), this, SLOT(envoyer_maj()));

}

Preferences::~Preferences()
{

}

void Preferences::envoyer_maj(){
    emit information_projet(nb_pelure_doignons->text().toInt(), choix_frequence_pelures_doignons->currentText().toInt(), previsualisation_rapide->text().toInt(), image_de_fond->isChecked());
    close();
}

