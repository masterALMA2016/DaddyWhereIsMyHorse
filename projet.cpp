#include "projet.h"

Projet::Projet(int x, int y, QWidget *parent):QMainWindow(parent)
{
    //parametrage fenetre
    longueur_fenetre = x;
    largeur_fenetre = y;

    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    creation_menu();

    //zone de travail
    QScrollArea *scr = new QScrollArea(this);


    dessin_courant = new Dessin(this);
    dessin_courant->setAlignment(Qt::AlignCenter);
    dessin_courant->set_color(Qt::black);
    scr->setWidget(dessin_courant);
    scr->setAlignment(Qt::AlignCenter);
    scr->setGeometry(200, 200, 600, 600);
    //ajout boutons





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

    QCheckBox *afficher_image = new QCheckBox(this);
    afficher_image->setText("Afficher image");
    afficher_image->setGeometry(scrollarea_zone_images->geometry().width()+10, barre_menu->geometry().height(), 120, 20);

    QCheckBox *afficher_dessin = new QCheckBox(this);
    afficher_dessin->setText("Afficher dessin");
    afficher_dessin->setGeometry(scrollarea_zone_images->geometry().width()+10, barre_menu->geometry().height()+20, 120, 20);

    QCheckBox *afficher_pelures_doigons = new QCheckBox(this);
    afficher_pelures_doigons->setText("Afficher pelures d'oigons");
    afficher_pelures_doigons->setGeometry(scrollarea_zone_images->geometry().width()+130, barre_menu->geometry().height(), 190, 20);

    QPushButton *previsualisation = new QPushButton(this);
    previsualisation->setGeometry(scrollarea_zone_images->geometry().width()+330, barre_menu->geometry().height(), 50, 40);
    QPixmap image_oeil("../DaddyWhereIsMyHorse/oeil.png");
    image_oeil = image_oeil.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_oeil(image_oeil);
    previsualisation->setIcon(icone_oeil);
    previsualisation->setIconSize(image_oeil.rect().size());

    QPushButton *precedent = new QPushButton(this);
    precedent->setGeometry(scrollarea_zone_images->geometry().width()+390, barre_menu->geometry().height(), 50, 40);
    QPixmap image_precedent("../DaddyWhereIsMyHorse/fleche_gauche.png");
    image_precedent = image_precedent.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_precedent(image_precedent);
    precedent->setIcon(icone_precedent);
    precedent->setIconSize(image_precedent.rect().size());

    QPushButton *suivant = new QPushButton(this);
    suivant->setGeometry(scrollarea_zone_images->geometry().width()+450, barre_menu->geometry().height(), 50, 40);
    QPixmap image_suivant("../DaddyWhereIsMyHorse/fleche_droite.png");
    image_suivant = image_suivant.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_suivant(image_suivant);
    suivant->setIcon(icone_suivant);
    suivant->setIconSize(image_suivant.rect().size());

    QPushButton *sauvegarder = new QPushButton(this);
    sauvegarder->setGeometry(scrollarea_zone_images->geometry().width()+510, barre_menu->geometry().height(), 50, 40);
    QPixmap image_sauvegarder("../DaddyWhereIsMyHorse/sauvegarder.png");
    image_sauvegarder = image_sauvegarder.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_sauvegarder(image_sauvegarder);
    sauvegarder->setIcon(icone_sauvegarder);
    sauvegarder->setIconSize(image_sauvegarder.rect().size());

    QPushButton *undo = new QPushButton(this);
    undo->setGeometry(scrollarea_zone_images->geometry().width()+570, barre_menu->geometry().height(), 50, 40);
    QPixmap image_undo("../DaddyWhereIsMyHorse/undo.png");
    image_undo = image_undo.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_undo(image_undo);
    undo->setIcon(icone_undo);
    undo->setIconSize(image_undo.rect().size());

    //pour la couleur du crayon
    couleur = new QPushButton(this);
    couleur->setGeometry(scrollarea_zone_images->geometry().width()+630, barre_menu->geometry().height() ,50 ,40);
    couleur->setStyleSheet("background: black");
    connect(couleur, SIGNAL(clicked()), this, SLOT(changer_couleur()));

    //pour utiliser le crayon
    QPushButton *crayon = new QPushButton(this);
    crayon->setGeometry(scrollarea_zone_images->geometry().width()+690, barre_menu->geometry().height(), 50, 40);
    QPixmap icone("../DaddyWhereIsMyHorse/crayon.png");
    icone = icone.scaledToWidth(35, Qt::FastTransformation);
    QIcon i(icone);
    crayon->setIcon(i);
    crayon->setIconSize(icone.rect().size());

    //pour utiliser la gomme
    QPushButton *gomme = new QPushButton(this);
    gomme->setGeometry(scrollarea_zone_images->geometry().width()+750, barre_menu->geometry().height(), 50, 40);
    QPixmap icone_gomme("../DaddyWhereIsMyHorse/gomme.png");
    icone_gomme = icone_gomme.scaledToWidth(35, Qt::FastTransformation);
    QIcon i2(icone_gomme);
    gomme->setIcon(i2);
    gomme->setIconSize(icone.rect().size());
}

void Projet::creation_menu(){
    //barre de menu
    barre_menu = new QMenuBar(this);
    barre_menu->setVisible(true);
    setMenuBar(barre_menu);

    //menu fichier
    QMenu *fichier = new QMenu("Fichier");
    barre_menu->addMenu(fichier);

    QAction *nouveau = new QAction(this);
    nouveau->setText(QString::fromUtf8("Nouveau"));
    nouveau->setShortcut(QKeySequence("CTRL+N"));
    fichier->addAction(nouveau);

    QAction *ouvrir = new QAction(this);
    ouvrir->setText(QString::fromUtf8("Ouvrir"));
    ouvrir->setShortcut(QKeySequence("CTRL+O"));
    fichier->addAction(ouvrir);

    QAction *enregistrer = new QAction(this);
    enregistrer->setText(QString::fromUtf8("Enregistrer"));
    enregistrer->setShortcut(QKeySequence("CTRL+S"));
    fichier->addAction(enregistrer);

    QAction *exporter_la_video = new QAction(this);
    exporter_la_video->setText(QString::fromUtf8("Exporter la viéo"));
    exporter_la_video->setShortcut(QKeySequence("CTRL+V"));
    fichier->addAction(exporter_la_video);

    QAction *exporter_les_images = new QAction(this);
    exporter_les_images->setText(QString::fromUtf8("Exporter les images"));
    exporter_les_images->setShortcut(QKeySequence("CTRL+I"));
    fichier->addAction(exporter_les_images);

    QAction *apercu = new QAction(this);
    apercu->setText(QString::fromUtf8("Aperçu"));
    apercu->setShortcut(QKeySequence("CTRL+N"));
    fichier->addAction(apercu);

    //menu edition
    QMenu *edition = new QMenu("Edition");
    barre_menu->addMenu(edition);

    QAction *preference = new QAction(this);
    preference->setText(QString::fromUtf8("Préférences"));
    preference->setShortcut(QKeySequence("CTRL+P"));
    edition->addAction(preference);

    edition->addSeparator();

    QAction *annuler = new QAction(this);
    annuler->setText(QString::fromUtf8("Annuler"));
    annuler->setShortcut(QKeySequence("CTRL+Z"));
    edition->addAction(annuler);

    QAction *afficher_images = new QAction(this);
    afficher_images->setText(QString::fromUtf8("Afficher images"));
    afficher_images->setShortcut(QKeySequence("CTRL+1"));
    edition->addAction(afficher_images);

    QAction *afficher_dessins = new QAction(this);
    afficher_dessins->setText(QString::fromUtf8("Afficher dessins"));
    afficher_dessins->setShortcut(QKeySequence("CTRL+2"));
    edition->addAction(afficher_dessins);

    QAction *afficher_pelures_doigons = new QAction(this);
    afficher_pelures_doigons->setText(QString::fromUtf8("Afficher pelures d'oignons"));
    afficher_pelures_doigons->setShortcut(QKeySequence("CTRL+3"));
    edition->addAction(afficher_pelures_doigons);

    QAction *previsualisation_rapide = new QAction(this);
    previsualisation_rapide->setText(QString::fromUtf8("Prévisualisation rapide"));
    previsualisation_rapide->setShortcut(QKeySequence("CTRL+R"));
    edition->addAction(previsualisation_rapide);

    QAction *suivant = new QAction(this);
    suivant->setText(QString::fromUtf8("Suivant"));
    suivant->setShortcut(QKeySequence("CTRL+right"));
    edition->addAction(suivant);

    QAction *precedent = new QAction(this);
    precedent->setText(QString::fromUtf8("Précédent"));
    precedent->setShortcut(QKeySequence("CTRL+left"));
    edition->addAction(precedent);

    QAction *crayon = new QAction(this);
    crayon->setText(QString::fromUtf8("Crayon"));
    crayon->setShortcut(QKeySequence("CTRL+C"));
    edition->addAction(crayon);

    QAction *gomme = new QAction(this);
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
        qd->setCurrentColor(dessin_courant->get_color());
        connect(qd, SIGNAL(colorSelected(QColor)), this, SLOT(couleur_choisie(QColor)));
        qd->open();

}

void Projet::couleur_choisie(QColor nouvelle_couleur){
    couleur->setStyleSheet("background-color:"+nouvelle_couleur.name()+";");
    dessin_courant->set_color(nouvelle_couleur);
}
