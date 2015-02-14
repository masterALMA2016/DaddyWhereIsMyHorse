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

    int longueur_fenetre;
    int largeur_fenetre;

    Dessin *dessin_courant;
    QPushButton *couleur;

    QMenuBar *barre_menu;

    std::vector<ImageClickable*> mes_images;
    QWidget *zone_images;
};

#endif // PROJET_H
