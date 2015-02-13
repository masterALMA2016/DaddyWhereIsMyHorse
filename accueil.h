#ifndef ACCUEIL_H
#define ACCUEIL_H
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
#include <QMenu>
#include <QMenuBar>
#include "dessin.h"

class Accueil : public QMainWindow
{
    Q_OBJECT

public:
    explicit Accueil(QWidget *parent = 0);
    ~Accueil();
       void projet();

public slots:
    void ouvrir_projet();
    void dessin(int x, int y);

private:
    Dessin *d;
    int longueur;
    int largeur;
    //Pour la "fenetre" d'accueil
    QPushButton *charger_projet;
    QPushButton *nouveau_projet;
    QLabel *label;

    //Pour la fenetre de projet
};

#endif // ACCUEIL_H
