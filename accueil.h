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

public slots:
    void ouvrir_projet();
    void creer_projet();
    void recuperer_informations(std::string nom_projet, std::string chemin_projet, std::string chemin_video, std::string frequence);

private:

    int longueur_fenetre;
    int largeur_fenetre;

    QPushButton *charger_projet;
    QPushButton *nouveau_projet;

    QLabel *message_accueil;
};

#endif // ACCUEIL_H
