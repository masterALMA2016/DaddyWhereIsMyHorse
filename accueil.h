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
#include <QVBoxLayout>
#include <iostream>
#include <QTextStream>
#include "creationprojet.h"
#include "projet.h"

class Accueil : public QMainWindow
{
    Q_OBJECT

public:
    explicit Accueil(QWidget *parent = 0);
    ~Accueil();

public slots:
    void ouvrir_projet();
    void creer_projet();
    void recuperer_informations(QString chemin_projet, QString frequence);


private:

    int longueur_fenetre;
    int largeur_fenetre;

    QLabel *probleme_ouverture_projet;
    QLabel *message_accueil;

    QPushButton *charger_projet;
    QPushButton *nouveau_projet;


};

#endif // ACCUEIL_H
