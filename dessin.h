#ifndef DESSIN_H
#define DESSIN_H

#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include "histo.h"

class Dessin: public QLabel
{
    Q_OBJECT

public:
    explicit Dessin(int longueur, int largeur, QWidget * parent = 0);
    ~Dessin();
    QColor get_color();
    QPixmap get_image();
    void set_color(QColor couleur);
    void set_utiliser_crayon(bool choix);
    void set_dessin(QPixmap image);
    void changer_taille_crayon(int nouvelle_taille);
    void save(QString dossier, QString chemin_dessin, QString chemin_calque, std::string chemin_image_film, std::string chemin_dessin_film);
    void undo(QString dossier);
    bool to_save();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();

private:
    QPixmap dessin;
    QPixmap ancien;
    QPen crayon;
    QCursor curseur;
    QPixmap image_souris;

    std::string path_souris;

    bool sauvegarder;
    bool tracer_ligne;
    bool utiliser_crayon;

    int x;
    int y;
};

#endif // DESSIN_H
