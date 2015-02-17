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
#include <QComboBox>
#include <QDir>
#include "dessin.h"
#include "imageclickable.h"

class Projet: public QMainWindow
{

    Q_OBJECT

public:
    explicit Projet(int x, int y, QString frequence, QString dossier, QWidget *parent = 0);
    ~Projet();


public slots:
    void changer_couleur();
    void couleur_choisie(QColor nouvelle_couleur);
    void changer_taille_crayon(int taille);
    void utiliser_gomme();
    void utiliser_crayon();
    void afficher(std::string path_image_film, std::string path_dessin, int index);
    void save();

private:

    void creation_menu();
    void importer_images();

    int current_index;
    int taille_crayon;
    int longueur_fenetre;
    int largeur_fenetre;

    QString frequence_video;
    QString dossier_projet;

    std::vector<ImageClickable*> mes_images;

    QLabel *image_fond;
    Dessin *dessin_courant;
    QColor couleur_courante;
    QComboBox *choix_taille_crayon;
    QPushButton *couleur;

    QMenuBar *barre_menu;

    QScrollArea *zone_de_travail;
    QVBoxLayout *layout_zone_images;
    QWidget *zone_images;
};

#endif // PROJET_H
