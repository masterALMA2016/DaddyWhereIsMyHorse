#ifndef PROJET_H
#define PROJET_H
#include <QMainWindow>
#include <QRect>
#include <QDesktopWidget>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QPixmap>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QObject>
#include <string>
#include <QMenuBar>
#include <QMenu>
#include <vector>
#include <iostream>
#include <QEvent>
#include <QDockWidget>
#include <QPainter>
#include <QColorDialog>
#include <QIcon>
#include <QCheckBox>
#include "dessin.h"
#include "imageclickable.h"

class Projet: public QMainWindow
{

    Q_OBJECT

public:
    explicit Projet(int x, int y, QWidget *parent = 0);
    ~Projet();

public slots:
    void changer_couleur();
    void couleur_choisie(QColor nouvelle_couleur);

private:

    void creation_menu();

    int longueur_fenetre;
    int largeur_fenetre;

    Dessin *dessin_courant;
    QPushButton *couleur;

    //barre de menu
    QMenuBar *barre_menu;
    QMenu *fichier;
    QAction *nouveau;
    QAction *ouvrir;
    QAction *enregistrer;
    QAction *exporter_la_video;
    QAction *exporter_les_images;
    QAction *apercu;

    QMenu *edition;
    QAction *preference;
    QAction *annuler;
    QAction *afficher_images;
    QAction *afficher_dessins;
    QAction *afficher_pelures_doigons;
    QAction *previsualisation_rapide;
    QAction *suivant;
    QAction *precedent;
    QAction *crayon;
    QAction *gomme;

    std::vector<ImageClickable*> mes_images;
    QWidget *zone_images;
};

#endif // PROJET_H
