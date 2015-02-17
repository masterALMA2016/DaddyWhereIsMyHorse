#include "projet.h"
#include <string>
#include <iomanip>
Projet::Projet(int x, int y, QString frequence, QString dossier, QWidget *parent):QMainWindow(parent), mes_pelures(5)
{
    current_index = 0;
    taille_crayon = 4;
    nombre_de_pelures_doignons = 5;
    frequence_pelures_doignons = 1;
    previsualisation_rapide = 10;
    frequence_video = frequence;
    dossier_projet = dossier;
    //parametrage fenetre
    longueur_fenetre = x;
    largeur_fenetre = y;




    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    creation_menu();

    scrollarea_zone_images = new QScrollArea(this);
    layout_zone_images = new QVBoxLayout();
    importer_images();

    zone_images = new QWidget(this);
    zone_images->setLayout(layout_zone_images);
    scrollarea_zone_images->setWidget(zone_images);
    scrollarea_zone_images->setGeometry(0, barre_menu->geometry().y()+barre_menu->height(), 205, largeur_fenetre-barre_menu->geometry().height());

    image_fond = new QLabel(this);
    image_fond->setAlignment(Qt::AlignCenter);
    image_fond->setStyleSheet("background-color: transparent");

    initialistaion_mes_pelures_doignons();

    zone_de_travail = new QScrollArea(this);

    QPixmap image_init_espace_travail((mes_images.at(0))->get_path_image_film().c_str());
    image_fond->setPixmap(image_init_espace_travail);

    dessin_courant = new Dessin(image_init_espace_travail.width(), image_init_espace_travail.height(), this);
    dessin_courant->setAlignment(Qt::AlignCenter);
    dessin_courant->set_color(Qt::black);
    std::string path_init_dessin = mes_images.at(0)->get_path_dessin().c_str();

    if(!path_init_dessin.empty()){
        QPixmap dessin_init(path_init_dessin.c_str());
        dessin_courant->set_dessin(dessin_init);
    }

    zone_de_travail->setWidget(dessin_courant);

    couleur_courante = Qt::black;
    zone_de_travail->setWidget(dessin_courant);
    zone_de_travail->setAlignment(Qt::AlignCenter);
    zone_de_travail->setStyleSheet("background: transparent");

    afficher_image = new QCheckBox(this);
    afficher_image->setText("Afficher image");
    afficher_image->setGeometry(scrollarea_zone_images->geometry().width() + 10, barre_menu->geometry().height(), 120, 20);
    afficher_image->setChecked(true);
    connect(afficher_image, SIGNAL(clicked()), this, SLOT(changer_affichage_image()));


    afficher_dessin = new QCheckBox(this);
    afficher_dessin->setText("Afficher dessin");
    afficher_dessin->setGeometry(scrollarea_zone_images->geometry().width() + 10, barre_menu->geometry().height() + 20, 120, 20);
    afficher_dessin->setChecked(true);
    connect(afficher_dessin, SIGNAL(clicked()), this, SLOT(changer_affichage_dessin()));

    afficher_pelures_doigons = new QCheckBox(this);
    afficher_pelures_doigons->setText("Afficher pelures d'oigons");
    afficher_pelures_doigons->setGeometry(scrollarea_zone_images->geometry().width() + 130, barre_menu->geometry().height(), 190, 20);
    connect(afficher_pelures_doigons, SIGNAL(clicked()), this, SLOT(changer_affichage_pelures_doignons()));

    QPushButton *previsualisation = new QPushButton(this);
    previsualisation->setGeometry(scrollarea_zone_images->geometry().width() + 330, barre_menu->geometry().height(), 50, 40);
    QPixmap image_oeil("../DaddyWhereIsMyHorse/oeil.png");
    image_oeil = image_oeil.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_oeil(image_oeil);
    previsualisation->setIcon(icone_oeil);
    previsualisation->setIconSize(image_oeil.rect().size());

    QPushButton *precedent = new QPushButton(this);
    precedent->setGeometry(scrollarea_zone_images->geometry().width() + 390, barre_menu->geometry().height(), 50, 40);
    QPixmap image_precedent("../DaddyWhereIsMyHorse/fleche_gauche.png");
    image_precedent = image_precedent.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_precedent(image_precedent);
    precedent->setIcon(icone_precedent);
    precedent->setIconSize(image_precedent.rect().size());
    connect(precedent, SIGNAL(clicked()), this, SLOT(image_precedente()));


    QPushButton *suivant = new QPushButton(this);
    suivant->setGeometry(scrollarea_zone_images->geometry().width()+450, barre_menu->geometry().height(), 50, 40);
    QPixmap image_suivant("../DaddyWhereIsMyHorse/fleche_droite.png");
    image_suivant = image_suivant.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_suivant(image_suivant);
    suivant->setIcon(icone_suivant);
    suivant->setIconSize(image_suivant.rect().size());
    connect(suivant, SIGNAL(clicked()), this, SLOT(image_suivante()));


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
    QPixmap image_crayon("../DaddyWhereIsMyHorse/crayon.png");
    image_crayon = image_crayon.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_crayon(image_crayon);
    crayon->setIcon(icone_crayon);
    crayon->setIconSize(image_crayon.rect().size());
    connect(crayon, SIGNAL(clicked()), this, SLOT(utiliser_crayon()));

    //pour utiliser la gomme
    QPushButton *gomme = new QPushButton(this);
    gomme->setGeometry(scrollarea_zone_images->geometry().width()+750, barre_menu->geometry().height(), 50, 40);
    QPixmap image_gomme("../DaddyWhereIsMyHorse/gomme.png");
    image_gomme = image_gomme.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_gomme(image_gomme);
    gomme->setIcon(icone_gomme);
    gomme->setIconSize(image_crayon.rect().size());
    connect(gomme, SIGNAL(clicked()), this, SLOT(utiliser_gomme()));

    choix_taille_crayon = new QComboBox(this);

    int diametre_crayon = 4;
    int pos = 0;
    while(diametre_crayon < 30){

        QPixmap image_taille_crayon(diametre_crayon, diametre_crayon);
        image_taille_crayon.fill(Qt::transparent);

        QPen crayon_taille_crayon(Qt::black);
        crayon_taille_crayon.setCapStyle(Qt::RoundCap);
        crayon_taille_crayon.setWidth(diametre_crayon);

        QPainter paint(&image_taille_crayon);
        paint.setPen(crayon_taille_crayon);
        paint.drawPoint(diametre_crayon/2, diametre_crayon/2);

        QString string_taille_crayon = QString::number(diametre_crayon);
        choix_taille_crayon->addItem(string_taille_crayon);
        choix_taille_crayon->setItemIcon(pos, image_taille_crayon);

        pos++;
        diametre_crayon += 4;
    }

    changer_taille_crayon(taille_crayon);

    choix_taille_crayon->setIconSize(QSize(50, 50));
    choix_taille_crayon->setGeometry(scrollarea_zone_images->geometry().width()+810, barre_menu->geometry().height(), 70, 40);

    connect(choix_taille_crayon, SIGNAL(currentIndexChanged(int)), this, SLOT(changer_taille_crayon(int)));
    connect(sauvegarder, SIGNAL(clicked()), this, SLOT(save()));

    image_fond->setGeometry(scrollarea_zone_images->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-scrollarea_zone_images->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));
    for(int i = 0; i < mes_pelures.size(); i++){
        mes_pelures.at(i)->setGeometry(scrollarea_zone_images->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-scrollarea_zone_images->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));
    }
    zone_de_travail->setGeometry(scrollarea_zone_images->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-scrollarea_zone_images->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));


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
    connect(enregistrer, SIGNAL(triggered()), this, SLOT(save()));

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
    connect(afficher_images, SIGNAL(triggered()), this, SLOT(changer_affichage_image()));

    QAction *afficher_dessins = new QAction(this);
    afficher_dessins->setText(QString::fromUtf8("Afficher dessins"));
    afficher_dessins->setShortcut(QKeySequence("CTRL+2"));
    edition->addAction(afficher_dessins);
    connect(afficher_dessins, SIGNAL(triggered()), this, SLOT(changer_affichage_dessin()));

    QAction *afficher_pelures_doigon = new QAction(this);
    afficher_pelures_doigon->setText(QString::fromUtf8("Afficher pelures d'oignons"));
    afficher_pelures_doigon->setShortcut(QKeySequence("CTRL+3"));
    edition->addAction(afficher_pelures_doigon);
    connect(afficher_pelures_doigon, SIGNAL(triggered()), this, SLOT(action_changer_affichage_pelures_doignons()));

    QAction *previsualisation_rapide = new QAction(this);
    previsualisation_rapide->setText(QString::fromUtf8("Prévisualisation rapide"));
    previsualisation_rapide->setShortcut(QKeySequence("CTRL+R"));
    edition->addAction(previsualisation_rapide);

    QAction *suivant = new QAction(this);
    suivant->setText(QString::fromUtf8("Suivant"));
    suivant->setShortcut(QKeySequence("CTRL+right"));
    edition->addAction(suivant);
    connect(suivant, SIGNAL(triggered()), this, SLOT(image_suivante()));

    QAction *precedent = new QAction(this);
    precedent->setText(QString::fromUtf8("Précédent"));
    precedent->setShortcut(QKeySequence("CTRL+left"));
    edition->addAction(precedent);
    connect(precedent, SIGNAL(triggered()), this, SLOT(image_precedente()));

    QAction *crayon = new QAction(this);
    crayon->setText(QString::fromUtf8("Crayon"));
    crayon->setShortcut(QKeySequence("CTRL+C"));
    edition->addAction(crayon);
    connect(crayon, SIGNAL(triggered()), this, SLOT(utiliser_crayon()));

    QAction *gomme = new QAction(this);
    gomme->setText(QString::fromUtf8("Gomme"));
    gomme->setShortcut(QKeySequence("CTRL+G"));
    edition->addAction(gomme);
    connect(gomme, SIGNAL(triggered()), this, SLOT(utiliser_gomme()));


}

Projet::~Projet()
{
    delete(image_fond);
    delete(dessin_courant);
    delete(choix_taille_crayon);
    delete(couleur);
    delete(barre_menu);
    delete(zone_de_travail);
    delete(layout_zone_images);
    delete(zone_images);
    delete(scrollarea_zone_images);

    for(int i = 0; i<mes_images.size(); i++){
        delete(mes_images.at(i));
    }
}

void Projet::changer_couleur(){
        QColor nouvelle_couleur;
        QColorDialog *color_dialog = new QColorDialog(this);
        color_dialog->setModal(true);
        color_dialog->setCurrentColor(dessin_courant->get_color());
        connect(color_dialog, SIGNAL(colorSelected(QColor)), this, SLOT(couleur_choisie(QColor)));
        color_dialog->open();

}

void Projet::couleur_choisie(QColor nouvelle_couleur){
    couleur->setStyleSheet("background-color:" + nouvelle_couleur.name() + ";");
    dessin_courant->set_color(nouvelle_couleur);
    couleur_courante=nouvelle_couleur;
}

void Projet::changer_taille_crayon(int taille){
    QString nouvelle_taille = choix_taille_crayon->currentText();
    dessin_courant->changer_taille_crayon(nouvelle_taille.toInt());
    taille_crayon = nouvelle_taille.toInt();
}

void Projet::utiliser_gomme(){
    dessin_courant->set_utiliser_crayon(false);
}

void Projet::utiliser_crayon(){
    dessin_courant->set_utiliser_crayon(true);
    dessin_courant->set_color(couleur_courante);
}

void Projet::importer_images(){
    QDir chemin_image(dossier_projet+"/images_video");
    chemin_image.setNameFilters(QStringList()<<"*.png");
    QStringList liste_images_film = chemin_image.entryList();

    QDir chemin_dessin(dossier_projet+"/dessins");
    chemin_dessin.setNameFilters(QStringList()<<"*.png");
    QStringList liste_dessin = chemin_dessin.entryList();

    for(int i = 0; i < liste_images_film.size(); i++){

        ImageClickable *image = new ImageClickable(chemin_image.path().toStdString() + "/" + liste_images_film.at(i).toStdString(), i);
        connect(image, SIGNAL(clicked(std::string,std::string, int)), this, SLOT(afficher(std::string, std::string, int)));

        if(liste_dessin.contains("dessin" + QString::number(i + 1) + ".png")){
            image->changer_image(chemin_dessin.path() + "/dessin" + QString::number(i + 1) + ".png");
        }

        layout_zone_images->addWidget(image);
        mes_images.push_back(image);
    }
}

void Projet::afficher(std::string path_image_film, std::string path_dessin, int index){
    QPixmap afficher_image_film(path_image_film.c_str());
    image_fond->setPixmap(afficher_image_film);
    current_index = index;
    affichage_pelures_doigons();

    dessin_courant = new Dessin(afficher_image_film.width(), afficher_image_film.height(), this);
    dessin_courant->setAlignment(Qt::AlignCenter);
    dessin_courant->set_color(Qt::black);

    if(!path_dessin.empty()){
        QPixmap afficher_dessin(path_dessin.c_str());
        dessin_courant->set_dessin(afficher_dessin);
    }

    dessin_courant->changer_taille_crayon(taille_crayon);

    zone_de_travail->setWidget(dessin_courant);
    dessin_courant->set_color(couleur_courante);
}

void Projet::save(){
    QString chemin_sauvegarde = dossier_projet + "/dessins/dessin" + QString::number(current_index + 1) + ".png";
    dessin_courant->save(chemin_sauvegarde);
    QPixmap dessin_temp = dessin_courant->get_image();
    dessin_temp = dessin_temp.scaledToWidth(160,  Qt::FastTransformation);
    mes_images.at(current_index)->setPixmap(dessin_temp);
    mes_images.at(current_index)->set_path_dessin(chemin_sauvegarde.toStdString());
}

void Projet::image_suivante(){
    if(current_index < mes_images.size()){
        current_index++;
        afficher(mes_images.at(current_index)->get_path_image_film(), mes_images.at(current_index)->get_path_dessin(), current_index);
    }
}

void Projet::image_precedente(){
    if(current_index>=0){
        current_index--;
        afficher(mes_images.at(current_index)->get_path_image_film(), mes_images.at(current_index)->get_path_dessin(), current_index);
    }
}

void Projet::changer_affichage_image(){
    image_fond->setVisible(!image_fond->isVisible());
    for(int i = 0; i<mes_images.size(); i++){
        mes_images.at(i)->set_affichage_image(!image_fond->isVisible());
    }
    if(image_fond->isVisible()!=afficher_image->isChecked()){
        afficher_image->setChecked(!afficher_image->isChecked());
    }
}

void Projet::changer_affichage_dessin(){
    dessin_courant->setVisible(!dessin_courant->isVisible());
    for(int i = 0; i<mes_images.size(); i++){
        mes_images.at(i)->set_affichage_dessin(dessin_courant->isVisible());
    }
    if(dessin_courant->isVisible()!=afficher_dessin->isChecked()){
        afficher_dessin->setChecked(!afficher_dessin->isChecked());
    }
}

void Projet::affichage_pelures_doigons(){
    int i = current_index - 1;
    int max = nombre_de_pelures_doignons;
    int transparence = 200;
    int index_mes_pelures = 0;
    while(i > 0 && max != 0 && mes_pelures.size() > index_mes_pelures){
        if(!mes_images.at(i)->get_path_dessin().empty()){

            QPixmap nouvelle_pelure(mes_images.at(i)->get_path_dessin().c_str());

            QPixmap pelure_transparente(nouvelle_pelure.size());
            pelure_transparente.fill(Qt::transparent);
            QPainter painter_transparent(&pelure_transparente);
            painter_transparent.setCompositionMode(QPainter::CompositionMode_Source);
            painter_transparent.drawPixmap(0, 0, nouvelle_pelure);
            painter_transparent.setCompositionMode(QPainter::CompositionMode_DestinationIn);

            painter_transparent.fillRect(pelure_transparente.rect(), QColor(0, 0, 0, transparence));
            painter_transparent.end();
            transparence = transparence/2;
            nouvelle_pelure = pelure_transparente;

            mes_pelures.at(index_mes_pelures)->setPixmap(nouvelle_pelure);
            index_mes_pelures++;
            max--;
        }
        i = i - frequence_pelures_doignons;
    }
}

void Projet::initialistaion_mes_pelures_doignons(){
    for(int i = 0; i < mes_pelures.size(); i++){
        QLabel *temp = new QLabel(this);
        temp->setAlignment(Qt::AlignCenter);
        temp->setVisible(false);
        mes_pelures.at(i) = temp;
    }
}

void Projet::changer_affichage_pelures_doignons(){
    for(int i = 0; i<mes_pelures.size(); i++){
        mes_pelures.at(i)->setVisible(afficher_pelures_doigons->isChecked());
    }
}

void Projet::action_changer_affichage_pelures_doignons(){
    afficher_pelures_doigons->setChecked(!afficher_pelures_doigons->isChecked());
    changer_affichage_pelures_doignons();
}
