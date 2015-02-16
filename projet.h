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

private:

    void creation_menu();
    QComboBox *choix_taille_crayon;
    int longueur_fenetre;
    int largeur_fenetre;
    QString frequence;
    QString dossier_projet;
    Dessin *dessin_courant;
    QPushButton *couleur;
    QColor couleur_courante;
    //barre de menu
    QMenuBar *barre_menu;

    std::vector<ImageClickable*> mes_images;
    QWidget *zone_images;
};

#endif // PROJET_H
