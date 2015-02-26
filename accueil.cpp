#include "accueil.h"

Accueil::Accueil(QWidget *parent):QMainWindow(parent)
{
    longueur_fenetre = 1120;
    largeur_fenetre = 794;

    this->setWindowTitle("Accueil");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    message_accueil = new QLabel(this);
    message_accueil->setText("Pas de projet ouvert");
    message_accueil->setStyleSheet("font: 40pt");
    message_accueil->setGeometry(QRect(350, 250, 480, 80));

    QPixmap image(":/rsc/img/lecture.png");
    image = image.scaledToWidth(20);
    QIcon icone_bouton(image);

    nouveau_projet = new QPushButton("Nouveau projet", this);
    nouveau_projet->setGeometry(470, 350, 250, 50);
    nouveau_projet->setStyleSheet("font: 15pt");
    nouveau_projet->setIcon(icone_bouton);
    nouveau_projet->setIconSize(image.rect().size());

    charger_projet = new QPushButton("Charger projet", this);
    charger_projet->setGeometry(470, 450, 250, 50);
    charger_projet->setStyleSheet("font: 15pt");
    charger_projet->setIcon(icone_bouton);
    charger_projet->setIconSize(image.rect().size());

    QPalette couleur_texte;
    couleur_texte.setColor(QPalette::WindowText, Qt::red);

    probleme_ouverture_projet = new QLabel(this);
    probleme_ouverture_projet->setText(QString::fromUtf8("Ce répertoire ne correspond pas à un projet DaddyWhereIsMyHorse"));
    probleme_ouverture_projet->setPalette(couleur_texte);
    probleme_ouverture_projet->setVisible(false);
    probleme_ouverture_projet->setGeometry(390, 520, 500, 25);

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(creer_projet()));
    connect(charger_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));
}

Accueil::~Accueil()
{
    delete(charger_projet);
    delete(nouveau_projet);
    delete(message_accueil);
    delete(probleme_ouverture_projet);
}

void Accueil::creer_projet(){

    cp = new CreationProjet(this);
    connect(cp, SIGNAL(information_projet(QString, QString)), this, SLOT(recuperer_informations(QString, QString )));
    cp->show();
}

void Accueil::ouvrir_projet(){

    QFileDialog *test = new QFileDialog(this, QDir::home().path());
    QString path = test->getExistingDirectory();
    QFile file(path + "/dwimh.conf");

    if(!file.exists()){
        probleme_ouverture_projet->setVisible(true);
    }
    else{

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&file);
        QString frequence_video = flux.readLine();
        QString nb_pelures_doignons = flux.readLine();
        QString frequence_pelures_doignons = flux.readLine();
        QString nb_previsualisation = flux.readLine();
        QString afficher_image_fond = flux.readLine();
        projet = new Projet(longueur_fenetre, largeur_fenetre, frequence_video, nb_pelures_doignons.toInt(), frequence_pelures_doignons.toInt(), nb_previsualisation.toInt(),  afficher_image_fond.toInt(), path);
        projet->show();
        this->close();
    }
}

void Accueil::recuperer_informations(QString chemin_projet, QString frequence){
    Projet *projet = new Projet(longueur_fenetre, largeur_fenetre, frequence, 5, 1, 10, 0, chemin_projet);
    projet->show();
    this->close();
}

