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

class Accueil : public QMainWindow
{
    Q_OBJECT

public:
    explicit Accueil(QWidget *parent = 0);
    ~Accueil();
       void projet();

public slots:
    void ouvrir_projet();

private:
    int longueur;
    int largeur;
    //Pour la "fenetre" d'accueil
    QPushButton *charger_projet;
    QPushButton *nouveau_projet;
    QLabel *label;

    //Pour la fenetre de projet
};

#endif // ACCUEIL_H
