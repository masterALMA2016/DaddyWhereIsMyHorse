#include "projet.h"
#include <string>
#include <iomanip>
#include <boost/lexical_cast.hpp>


Projet::Projet(int x, int y, QString frequence, int nb_pelures_doignons, int new_frequence_pelures_doignons, int nb_previsualisation, bool afficher_image_fond, QString dossier, QWidget *parent):QMainWindow(parent), mes_pelures(10)
{
    current_index = 0;
    taille_crayon = 4;
    numero_derniere_image = 1;
    nombre_de_pelures_doignons = nb_pelures_doignons;
    frequence_pelures_doignons = new_frequence_pelures_doignons;
    previsualisation_rapide = nb_previsualisation;
    frequence_video = frequence;
    dossier_projet = dossier;
    image_de_fond = afficher_image_fond;
    gomme = false;
    //parametrage fenetre
    longueur_fenetre = x;
    largeur_fenetre = y;

    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);

    creation_menu();

    mes_label = new QListWidget(this);

    importer_images();

    mes_label->setCurrentRow(current_index);


    connect(mes_label, SIGNAL(clicked(QModelIndex)), this, SLOT(changer_index(QModelIndex)));

    mes_label->setGeometry(0, barre_menu->geometry().y()+barre_menu->height(), 205, largeur_fenetre-barre_menu->geometry().height());
    mes_label->setStyleSheet("QListWidget::item {border-bottom: 1px solid black;}");

    image_fond = new QLabel(this);
    image_fond->setAlignment(Qt::AlignCenter);
    image_fond->setStyleSheet("background-color: #7e7e7e");

    initialistaion_mes_pelures_doignons();

    zone_de_travail = new QScrollArea(this);

    QPixmap image_init_espace_travail((mes_images.at(0))->get_path_image_film().c_str());
    image_fond->setPixmap(image_init_espace_travail);

    dessin_courant = new Dessin(image_init_espace_travail.width(), image_init_espace_travail.height(),  this);
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

    afficher_image = new QToolButton(this);
    afficher_image->setEnabled(true);
    afficher_image->setToolTip("Afficher les image de la vidéo");

    afficher_image->setGeometry(mes_label->width() + 10, barre_menu->geometry().height(), 50, 40);
    afficher_image->setChecked(true);
    QPixmap image_image(":/rsc/img/film.png");
    image_image = image_image.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_image(image_image);
    afficher_image->setIcon(icone_image);
    afficher_image->setIconSize(image_image.rect().size());
    afficher_image->setDown(true);
    connect(afficher_image, SIGNAL(clicked()), this, SLOT(changer_affichage_image()));

    afficher_dessin = new QToolButton(this);
    afficher_dessin->setEnabled(true);
    afficher_dessin->setToolTip("Afficher les dessins");
    QPixmap image_dessin(":/rsc/img/dessin.png");
    image_dessin = image_dessin.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_dessin(image_dessin);
    afficher_dessin->setIcon(icone_dessin);
    afficher_dessin->setIconSize(image_dessin.rect().size());
    afficher_dessin->setDown(true);
    afficher_dessin->setGeometry(mes_label->width() + 70, barre_menu->geometry().height(), 50, 40);
    connect(afficher_dessin, SIGNAL(clicked()), this, SLOT(changer_affichage_dessin()));

    afficher_pelures_doigons = new QToolButton(this);
    afficher_pelures_doigons->setEnabled(true);
    afficher_pelures_doigons->setToolTip("Afficher les pelures d'oignon");

    QPixmap image_calque(":/rsc/img/calque.png");
    image_calque = image_calque.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_calque(image_calque);
    afficher_pelures_doigons->setIcon(icone_calque);
    afficher_pelures_doigons->setIconSize(image_calque.rect().size());
    afficher_pelure_down = false;
    afficher_pelures_doigons->setGeometry(mes_label->width() + 130, barre_menu->geometry().height(), 50, 40);
    connect(afficher_pelures_doigons, SIGNAL(clicked()), this, SLOT(action_changer_affichage_pelures_doignons()));



    QPushButton *previsualisation = new QPushButton(this);
    previsualisation->setGeometry(mes_label->width() + 190, barre_menu->geometry().height(), 50, 40);
    QPixmap image_oeil(":/rsc/img/oeil.png");
    image_oeil = image_oeil.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_oeil(image_oeil);
    previsualisation->setIcon(icone_oeil);
    previsualisation->setIconSize(image_oeil.rect().size());
    connect(previsualisation, SIGNAL(clicked()), this, SLOT(creation_previsualisation_rapide()));

    QPushButton *precedent = new QPushButton(this);
    precedent->setGeometry(mes_label->width() + 250, barre_menu->geometry().height(), 50, 40);
    QPixmap image_precedent(":/rsc/img/fleche_gauche.png");
    image_precedent = image_precedent.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_precedent(image_precedent);
    precedent->setIcon(icone_precedent);
    precedent->setIconSize(image_precedent.rect().size());
    connect(precedent, SIGNAL(clicked()), this, SLOT(image_precedente()));


    QPushButton *suivant = new QPushButton(this);
    suivant->setGeometry(mes_label->width() + 310 , barre_menu->geometry().height(), 50, 40);
    QPixmap image_suivant(":/rsc/img/fleche_droite.png");
    image_suivant = image_suivant.scaledToWidth(40, Qt::FastTransformation);
    QIcon icone_suivant(image_suivant);
    suivant->setIcon(icone_suivant);
    suivant->setIconSize(image_suivant.rect().size());
    connect(suivant, SIGNAL(clicked()), this, SLOT(image_suivante()));


    QPushButton *sauvegarder = new QPushButton(this);
    sauvegarder->setGeometry(mes_label->width() + 370, barre_menu->geometry().height(), 50, 40);
    QPixmap image_sauvegarder(":/rsc/img/sauvegarder.png");
    image_sauvegarder = image_sauvegarder.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_sauvegarder(image_sauvegarder);
    sauvegarder->setIcon(icone_sauvegarder);
    sauvegarder->setIconSize(image_sauvegarder.rect().size());

    QPushButton *undo = new QPushButton(this);
    undo->setGeometry(mes_label->width() + 430, barre_menu->geometry().height(), 50, 40);
    QPixmap image_undo(":/rsc/img/undo.png");
    image_undo = image_undo.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_undo(image_undo);
    undo->setIcon(icone_undo);
    undo->setIconSize(image_undo.rect().size());
    connect(undo, SIGNAL(clicked()), this, SLOT(undo()));

    //pour la couleur du crayon
    couleur = new QPushButton(this);
    couleur->setGeometry(mes_label->width() + 490, barre_menu->geometry().height() ,50 ,40);
    couleur->setStyleSheet("background: black");
    connect(couleur, SIGNAL(clicked()), this, SLOT(changer_couleur()));

    //pour utiliser le crayon
    QPushButton *crayon = new QPushButton(this);
    crayon->setGeometry(mes_label->width() + 550, barre_menu->geometry().height(), 50, 40);
    QPixmap image_crayon(":/rsc/img/crayon.png");
    image_crayon = image_crayon.scaledToWidth(35, Qt::FastTransformation);
    QIcon icone_crayon(image_crayon);
    crayon->setIcon(icone_crayon);
    crayon->setIconSize(image_crayon.rect().size());
    connect(crayon, SIGNAL(clicked()), this, SLOT(utiliser_crayon()));

    //pour utiliser la gomme
    QPushButton *gomme = new QPushButton(this);
    gomme->setGeometry(mes_label->width() + 610, barre_menu->geometry().height(), 50, 40);
    QPixmap image_gomme(":/rsc/img/gomme.png");
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

    changer_taille_crayon();

    choix_taille_crayon->setIconSize(QSize(50, 50));
    choix_taille_crayon->setGeometry(mes_label->width() + 670, barre_menu->geometry().height(), 70, 40);

    connect(choix_taille_crayon, SIGNAL(currentIndexChanged(int)), this, SLOT(changer_taille_crayon()));
    connect(sauvegarder, SIGNAL(clicked()), this, SLOT(save()));

    image_fond->setGeometry(mes_label->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-mes_label->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));
    for(unsigned int i = 0; i < mes_pelures.size(); i++){
        mes_pelures.at(i)->setGeometry(mes_label->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-mes_label->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));
    }
    zone_de_travail->setGeometry(mes_label->geometry().width(), barre_menu->geometry().height()+50, longueur_fenetre-mes_label->geometry().width(), largeur_fenetre-(barre_menu->geometry().height()+50));


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
    connect(nouveau, SIGNAL(triggered()), this, SLOT(nouveau_projet()));

    QAction *ouvrir = new QAction(this);
    ouvrir->setText(QString::fromUtf8("Ouvrir"));
    ouvrir->setShortcut(QKeySequence("CTRL+O"));
    fichier->addAction(ouvrir);
    connect(ouvrir, SIGNAL(triggered()), this, SLOT(ouvrir_projet()));

    QAction *enregistrer = new QAction(this);
    enregistrer->setText(QString::fromUtf8("Enregistrer"));
    enregistrer->setShortcut(QKeySequence("CTRL+S"));
    fichier->addAction(enregistrer);
    connect(enregistrer, SIGNAL(triggered()), this, SLOT(save()));

    QAction *exporter_la_video = new QAction(this);
    exporter_la_video->setText(QString::fromUtf8("Exporter la vidéo"));
    exporter_la_video->setShortcut(QKeySequence("CTRL+V"));
    fichier->addAction(exporter_la_video);
    connect(exporter_la_video, SIGNAL(triggered()), this, SLOT(exporter_video()));

    QAction *exporter_les_images = new QAction(this);
    exporter_les_images->setText(QString::fromUtf8("Exporter les images"));
    exporter_les_images->setShortcut(QKeySequence("CTRL+I"));
    fichier->addAction(exporter_les_images);
    connect(exporter_les_images, SIGNAL(triggered()), this, SLOT(exporter_les_dessins()));

    QAction *apercu = new QAction(this);
    apercu->setText(QString::fromUtf8("Aperçu"));
    apercu->setShortcut(QKeySequence("CTRL+A"));
    fichier->addAction(apercu);
    connect(apercu, SIGNAL(triggered()), this, SLOT(apercu_video()));

    //menu edition
    QMenu *edition = new QMenu("Édition");
    barre_menu->addMenu(edition);

    QAction *preference = new QAction(this);
    preference->setText(QString::fromUtf8("Préférences"));
    preference->setShortcut(QKeySequence("CTRL+P"));
    edition->addAction(preference);
    connect(preference, SIGNAL(triggered()), this, SLOT(choisir_preferences()));

    edition->addSeparator();

    QAction *annuler = new QAction(this);
    annuler->setText(QString::fromUtf8("Annuler"));
    annuler->setShortcut(QKeySequence("CTRL+Z"));
    edition->addAction(annuler);
    connect(annuler, SIGNAL(triggered()), this, SLOT(undo()));

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
    connect(previsualisation_rapide, SIGNAL(triggered()), this, SLOT(creation_previsualisation_rapide()));


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

    for(unsigned int i = 0; i<mes_images.size(); i++){
        delete(mes_images.at(i));
    }
    std::cout<<"proj"<<std::endl;

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
    couleur_courante = nouvelle_couleur;
}

void Projet::changer_taille_crayon(){
    QString nouvelle_taille = choix_taille_crayon->currentText();
    dessin_courant->changer_taille_crayon(nouvelle_taille.toInt());
    taille_crayon = nouvelle_taille.toInt();
}

void Projet::utiliser_gomme(){
    gomme = true;
    dessin_courant->set_utiliser_crayon(false);
}

void Projet::utiliser_crayon(){
    gomme = false;
    dessin_courant->set_utiliser_crayon(true);
    dessin_courant->set_color(couleur_courante);
}

void Projet::importer_images(){
    QDir chemin_image(dossier_projet+"/images_video");
    chemin_image.setNameFilters(QStringList()<<"*.png");
    QStringList liste_images_film = chemin_image.entryList();

    QDir chemin_dessin(dossier_projet+"/calque");
    chemin_dessin.setNameFilters(QStringList()<<"*.png");
    QStringList liste_dessin = chemin_dessin.entryList();

    for(int i = 0; i < liste_images_film.size(); i++){
        QListWidgetItem *un_objet = new QListWidgetItem(mes_label);
        ImageClickable *image = new ImageClickable(chemin_image.path().toStdString() + "/" + liste_images_film.at(i).toStdString(), i);
        QString nom = liste_images_film.at(i);

        nom = nom.replace(0, 5, "calque");
        if(liste_dessin.contains( nom)){
            image->changer_image(chemin_dessin.path() + "/" + nom);
            numero_derniere_image = i+1;
        }
        mes_label->addItem(un_objet);
        un_objet->setSizeHint(QSize(image->width(), image->height()+5));
        mes_label->setItemWidget(un_objet, image);
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
    if(!afficher_dessin->isDown()){
        dessin_courant->setVisible(false);
    }
    if(gomme){
        utiliser_gomme();
    }

}

void Projet::save(){

    std::string zero = "";
    int nb_zero = boost::lexical_cast<std::string>(mes_images.size()).length() - boost::lexical_cast<std::string>(current_index+1).length();
    for(int i=0; i< nb_zero; i++){
        zero+="0";
    }
    if(current_index+1 > numero_derniere_image){
        numero_derniere_image = current_index +1;
    }
    QString chemin_sauvegarde_dessin = dossier_projet + "/dessins/dessin" + zero.c_str() + QString::number(current_index + 1) + ".png";
    QString chemin_sauvegarde_calque = dossier_projet + "/calque/calque" + zero.c_str() + QString::number(current_index + 1) + ".png";
    QString chemin_sauvegarde_avec_fond = dossier_projet + "/dessin_image_film/dessin_image_film" + zero.c_str() + QString::number(current_index + 1) + ".png";

    dessin_courant->save(dossier_projet, chemin_sauvegarde_dessin, chemin_sauvegarde_calque, mes_images.at(current_index)->get_path_image_film(), chemin_sauvegarde_avec_fond.toStdString());

    QPixmap dessin_temp = dessin_courant->get_image();
    dessin_temp = dessin_temp.scaledToWidth(180,  Qt::FastTransformation);
    mes_images.at(current_index)->setPixmap(dessin_temp);
    mes_images.at(current_index)->set_path_dessin(chemin_sauvegarde_calque.toStdString());
}

void Projet::image_suivante(){
   if(dessin_courant->to_save()){
       save();
   }
    if(current_index < mes_images.size()-1){
        current_index++;
        mes_label->setCurrentRow(current_index);

        afficher(mes_images.at(current_index)->get_path_image_film(), mes_images.at(current_index)->get_path_dessin(), current_index);
    }
}

void Projet::image_precedente(){
    if(dessin_courant->to_save()){
        save();
    }
    if(current_index>0){
        current_index--;
        mes_label->setCurrentRow(current_index);

        afficher(mes_images.at(current_index)->get_path_image_film(), mes_images.at(current_index)->get_path_dessin(), current_index);
    }
}

void Projet::changer_affichage_image(){
    image_fond->setVisible(!image_fond->isVisible());
    afficher_image->setDown(image_fond->isVisible());

    for(unsigned int i = 0; i<mes_images.size(); i++){
        mes_images.at(i)->set_affichage_image(!image_fond->isVisible());
    }
}

void Projet::changer_affichage_dessin(){
    dessin_courant->setVisible(!dessin_courant->isVisible());
    afficher_dessin->setDown(dessin_courant->isVisible());

    for(unsigned int i = 0; i<mes_images.size(); i++){
        mes_images.at(i)->set_affichage_dessin(dessin_courant->isVisible());
    }

}

void Projet::affichage_pelures_doigons(){
    int i = current_index - 1;
    int max = nombre_de_pelures_doignons;
    int transparence = 200;
    int index_mes_pelures = 0;


    while(i >= 0 && max != 0 && mes_pelures.size() > index_mes_pelures){
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
            transparence = transparence - 20;
            nouvelle_pelure = pelure_transparente;

            mes_pelures.at(index_mes_pelures)->setPixmap(nouvelle_pelure);
            index_mes_pelures++;
            max--;
        }
        i = i - frequence_pelures_doignons;
    }
    for(unsigned int j = index_mes_pelures; j<mes_pelures.size(); j++){
        mes_pelures.at(j)->setPixmap(QPixmap());
    }
}

void Projet::initialistaion_mes_pelures_doignons(){
    for(unsigned int i = 0; i < mes_pelures.size(); i++){
        QLabel *temp = new QLabel(this);
        temp->setAlignment(Qt::AlignCenter);
        temp->setVisible(false);
        mes_pelures.at(i) = temp;
    }
}

void Projet::changer_affichage_pelures_doignons(){

    afficher_pelure_down = !afficher_pelure_down;
    afficher_pelures_doigons->setDown(afficher_pelure_down);

    for(unsigned int i = 0; i<mes_pelures.size(); i++){
        mes_pelures.at(i)->setVisible(afficher_pelures_doigons->isDown());
    }
}

void Projet::action_changer_affichage_pelures_doignons(){
    changer_affichage_pelures_doignons();
}

void Projet::undo(){
    dessin_courant->undo(dossier_projet);
}

void Projet::creation_previsualisation_rapide(){
    QDir chemin_video(dossier_projet + "/videos");
    QDir chemin_dessins(dossier_projet + "/dessins");
    std::string nb_zero = boost::lexical_cast<std::string>(boost::lexical_cast<std::string>(mes_images.size()).length());

    std::string path_a_utiliser = chemin_dessins.path().toStdString() + "/dessin%0";
    if(image_de_fond){
        QDir chemin_dessins_video(dossier_projet + "/dessin_image_film");

        path_a_utiliser = chemin_dessins_video.path().toStdString() + "/dessin_image_film%0";;
    }
    int premiere_image = numero_derniere_image+1 - previsualisation_rapide;
    std::cout<<premiere_image<<std::endl;
    if(premiere_image<0){
        premiere_image = 0;
    }
    std::string str = "ffmpeg -y -f image2 -start_number " + boost::lexical_cast<std::string>(premiere_image) + " -r " + frequence_video.toStdString() + " -i " + path_a_utiliser + nb_zero + "d.png -vcodec mpeg4 " + chemin_video.path().toStdString() + "/previsualisation.avi";
    system(str.c_str());
    player = new Player(chemin_video.path() + "/previsualisation.avi");
    player->show();

}

void Projet::choisir_preferences(){
    Preferences *p = new Preferences(nombre_de_pelures_doignons, frequence_pelures_doignons, previsualisation_rapide, image_de_fond, this);
    connect(p, SIGNAL(information_projet(int,int,int,bool)), this, SLOT(maj_preferences(int,int,int,bool)));
    p->show();
}

void Projet::maj_preferences(int new_nb_pelures_doignons, int new_frequences_pelures_doignons, int new_previsualisation, bool new_image_fond){
    nombre_de_pelures_doignons = new_nb_pelures_doignons;
    frequence_pelures_doignons = new_frequences_pelures_doignons;
    previsualisation_rapide = new_previsualisation;
    image_de_fond = new_image_fond;

    QFile configuration(dossier_projet + "/dwimh.conf");
    configuration.open(QIODevice::WriteOnly);
    configuration.write(frequence_video.toStdString().c_str() );
    configuration.write("\n" );
    configuration.write(QString::number(nombre_de_pelures_doignons).toStdString().c_str());
    configuration.write("\n" );
    configuration.write(QString::number(frequence_pelures_doignons).toStdString().c_str());
    configuration.write("\n" );
    configuration.write(QString::number(previsualisation_rapide).toStdString().c_str());
    configuration.write("\n" );
    configuration.write(QString::number(image_de_fond).toStdString().c_str());
    configuration.close();

}

void Projet::nouveau_projet(){
    CreationProjet *cp = new CreationProjet(this);
    connect(cp, SIGNAL(information_projet(QString, QString)), this, SLOT(recuperer_informations(QString, QString )));
    cp->show();
}

void Projet::recuperer_informations(QString chemin_projet, QString frequence){

    Projet *projet = new Projet(longueur_fenetre, largeur_fenetre, frequence, 5, 1, 10, 0, chemin_projet);
    projet->show();
}

void Projet::ouvrir_projet(){

    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directoriy"), QDir::home().path(), QFileDialog::ShowDirsOnly);
    QFile file(path + "/dwimh.conf");
    if(!file.exists()){
        Erreur *erreur = new Erreur(this);
        erreur->show();

    }
    else{
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&file);
        QString frequence_video = flux.readLine();
        QString nb_pelures_doignons = flux.readLine();
        QString frequence_pelures_doignons = flux.readLine();
        QString nb_previsualisation = flux.readLine();
        QString afficher_image_fond = flux.readLine();
        Projet *projet = new Projet(longueur_fenetre, largeur_fenetre, frequence_video, nb_pelures_doignons.toInt(), frequence_pelures_doignons.toInt(), nb_previsualisation.toInt(),  afficher_image_fond.toInt(), path);
        projet->show();
    }
}

void Projet::apercu_video(){
    QString chemin_video = creer_ma_video();
    player = new Player(chemin_video + "/ma_video.avi");
    player->show();
}

void Projet::exporter_video(){

    creer_ma_video();

    QString dir_save = QDir::home().path() + "/DaddyWhereIsMyHorse.avi";
    QString save_here = QFileDialog::getSaveFileName(this, tr("Save File"),  dir_save);

    QDir dir_projet(dossier_projet);
    dir_projet.cd("videos");

    QFile ma_video(dir_projet.path()+"/ma_video.avi");
    ma_video.copy(save_here);
}

void Projet::exporter_les_dessins(){
    QString dir_save = QDir::home().path();
    QString save_here = QFileDialog::getExistingDirectory(this, tr("choisir un répertoire"),  dir_save, QFileDialog::ShowDirsOnly);
    std::string copier = "cp -R " + dossier_projet.toStdString() + "/dessins " + save_here.toStdString() + "/DessinsDaddyWhereIsMyHorse";
    system(copier.c_str());
}


QString Projet::creer_ma_video(){
    QDir chemin_video(dossier_projet + "/videos");
    QDir chemin_dessins(dossier_projet + "/dessins");
    std::string nb_zero = boost::lexical_cast<std::string>(boost::lexical_cast<std::string>(mes_images.size()).length());
    std::string path_a_utiliser = chemin_dessins.path().toStdString() + "/dessin%0";
    if(image_de_fond){
        QDir chemin_dessins_video(dossier_projet + "/dessin_image_film");

        path_a_utiliser = chemin_dessins_video.path().toStdString() + "/dessin_image_film%0";;
    }
    std::string str = "ffmpeg -y -f image2 -r " + frequence_video.toStdString() + " -i " + path_a_utiliser + nb_zero + "d.png -vcodec mpeg4 " + chemin_video.path().toStdString() + "/ma_video.avi";
    system(str.c_str());
    return chemin_video.path();
}

void Projet::changer_index(QModelIndex index){
    afficher(mes_images.at(index.row())->get_path_image_film(), mes_images.at(index.row())->get_path_dessin(), index.row());
}
