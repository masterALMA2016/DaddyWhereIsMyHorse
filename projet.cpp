#include "projet.h"

Projet::Projet(int x, int y, QWidget *parent):QMainWindow(parent)
{
    //parametrage fenetre
    longueur_fenetre = x;
    largeur_fenetre = y;

    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

   /* creation_menu();
    QCheckBox *afficher_image = new QCheckBox(this);
    afficher_image->setText("afficher image");
    */
    //zone de travail
    QScrollArea *scr = new QScrollArea(this);


    dessin_courant = new Dessin(this);
    dessin_courant->setAlignment(Qt::AlignCenter);
    scr->setWidget(dessin_courant);
    scr->setAlignment(Qt::AlignCenter);
    scr->setGeometry(200, 200, 600, 600);
    //ajout boutons

    //pour la couleur du crayon
    couleur = new QPushButton(this);
    couleur->setGeometry(longueur_fenetre-100, barre_menu->geometry().height() ,40 ,30);
    connect(couleur, SIGNAL(clicked()), this, SLOT(changer_couleur()));

    //pour utiliser le crayon
    QPushButton *crayon = new QPushButton(this);
    crayon->setGeometry(longueur_fenetre-50, barre_menu->geometry().height(), 50, 50);
    QPixmap icone("../DaddyWhereIsMyHorse/crayon.png");
    icone = icone.scaledToWidth(40, Qt::FastTransformation);
    QIcon i(icone);
    crayon->setIcon(i);
    crayon->setIconSize(icone.rect().size());

    //pour utiliser la gomme
    QPushButton *gomme = new QPushButton(this);
    gomme->setGeometry(longueur_fenetre-150, barre_menu->geometry().height(), 50, 50);
    QPixmap icone_gomme("../DaddyWhereIsMyHorse/gomme.png");
    icone_gomme = icone_gomme.scaledToWidth(40, Qt::FastTransformation);
    QIcon i2(icone_gomme);
    gomme->setIcon(i2);
    gomme->setIconSize(icone.rect().size());

    QScrollArea *scrollarea_zone_images = new QScrollArea(this);
    QVBoxLayout *layout_zone_images = new QVBoxLayout();


    for(int i=0; i<10; i++){
        ImageClickable *image=new ImageClickable("/home/Soge/Images/Wallpapers/game_of_thrones_016.jpg");
        layout_zone_images->addWidget(image);
        mes_images.push_back(image);
    }

    zone_images = new QWidget(this);
    zone_images->setLayout(layout_zone_images);
    scrollarea_zone_images->setWidget(zone_images);
    scrollarea_zone_images->setGeometry(0, barre_menu->geometry().y()+barre_menu->height(), 205, largeur_fenetre-barre_menu->geometry().height());

}

void Projet::creation_menu(){
    //barre de menu
    barre_menu = new QMenuBar(this);
    barre_menu->setVisible(true);
    setMenuBar(barre_menu);

    //menu fichier
    fichier = new QMenu("Fichier");
    barre_menu->addMenu(fichier);

    nouveau = new QAction(this);
    nouveau->setText(QString::fromUtf8("Nouveau"));
    nouveau->setShortcut(QKeySequence("CTRL+N"));
    fichier->addAction(nouveau);

    ouvrir = new QAction(this);
    ouvrir->setText(QString::fromUtf8("Ouvrir"));
    ouvrir->setShortcut(QKeySequence("CTRL+O"));
    fichier->addAction(ouvrir);

    enregistrer = new QAction(this);
    enregistrer->setText(QString::fromUtf8("Enregistrer"));
    enregistrer->setShortcut(QKeySequence("CTRL+S"));
    fichier->addAction(enregistrer);

    exporter_la_video = new QAction(this);
    exporter_la_video->setText(QString::fromUtf8("Exporter la viéo"));
    exporter_la_video->setShortcut(QKeySequence("CTRL+V"));
    fichier->addAction(exporter_la_video);

    exporter_les_images = new QAction(this);
    exporter_les_images->setText(QString::fromUtf8("Exporter les images"));
    exporter_les_images->setShortcut(QKeySequence("CTRL+I"));
    fichier->addAction(exporter_les_images);

    apercu = new QAction(this);
    apercu->setText(QString::fromUtf8("Aperçu"));
    apercu->setShortcut(QKeySequence("CTRL+N"));
    fichier->addAction(apercu);

    //menu edition
    edition = new QMenu("Edition");
    barre_menu->addMenu(edition);

    preference = new QAction(this);
    preference->setText(QString::fromUtf8("Préférences"));
    preference->setShortcut(QKeySequence("CTRL+P"));
    edition->addAction(preference);

    edition->addSeparator();

    annuler = new QAction(this);
    annuler->setText(QString::fromUtf8("Annuler"));
    annuler->setShortcut(QKeySequence("CTRL+Z"));
    edition->addAction(annuler);

    afficher_images = new QAction(this);
    afficher_images->setText(QString::fromUtf8("Afficher images"));
    afficher_images->setShortcut(QKeySequence("CTRL+1"));
    edition->addAction(afficher_images);

    afficher_dessins = new QAction(this);
    afficher_dessins->setText(QString::fromUtf8("Afficher dessins"));
    afficher_dessins->setShortcut(QKeySequence("CTRL+2"));
    edition->addAction(afficher_dessins);

    afficher_pelures_doigons = new QAction(this);
    afficher_pelures_doigons->setText(QString::fromUtf8("Afficher pelures d'oignons"));
    afficher_pelures_doigons->setShortcut(QKeySequence("CTRL+3"));
    edition->addAction(afficher_pelures_doigons);

    previsualisation_rapide = new QAction(this);
    previsualisation_rapide->setText(QString::fromUtf8("Prévisualisation rapide"));
    previsualisation_rapide->setShortcut(QKeySequence("CTRL+R"));
    edition->addAction(previsualisation_rapide);

    suivant = new QAction(this);
    suivant->setText(QString::fromUtf8("Suivant"));
    suivant->setShortcut(QKeySequence("CTRL+right"));
    edition->addAction(suivant);

    precedent = new QAction(this);
    precedent->setText(QString::fromUtf8("Précédent"));
    precedent->setShortcut(QKeySequence("CTRL+left"));
    edition->addAction(precedent);

    crayon = new QAction(this);
    crayon->setText(QString::fromUtf8("Crayon"));
    crayon->setShortcut(QKeySequence("CTRL+C"));
    edition->addAction(crayon);

    gomme = new QAction(this);
    gomme->setText(QString::fromUtf8("Gomme"));
    gomme->setShortcut(QKeySequence("CTRL+G"));
    edition->addAction(gomme);


}

Projet::~Projet()
{

}

void Projet::changer_couleur(){
        QColor col;
        QColorDialog *qd = new QColorDialog(this);
        qd->setModal(true);
        connect(qd, SIGNAL(colorSelected(QColor)), this, SLOT(couleur_choisie(QColor)));
        qd->open();

}

void Projet::couleur_choisie(QColor nouvelle_couleur){
    couleur->setStyleSheet("background-color:"+nouvelle_couleur.name()+";");
    dessin_courant->set_color(nouvelle_couleur);
}
