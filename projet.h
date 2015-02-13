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
#include "imageclickable.h"
#include <string>
#include <QMenuBar>
#include <QMenu>
#include "dessin.h"

class Projet: public QMainWindow
{

    Q_OBJECT
public:
    explicit Projet(int x, int y, QWidget *parent = 0);
    ~Projet();

public slots:
    void dessin(int x, int y);

private:
    Dessin *d;

    int longueur;
    int largeur;
    QMenuBar *barre_menu;
    ImageClickable *label1;
    QWidget *ma;
    QLabel *test2;

};

#endif // PROJET_H
