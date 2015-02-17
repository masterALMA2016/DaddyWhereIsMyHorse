#ifndef DESSIN_H
#define DESSIN_H

#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPixmap>

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
    void save(QString chemin);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();

private:
    QPen crayon;
    QPixmap dessin;

    bool tracer_ligne;
    bool utiliser_crayon;

    int x;
    int y;
};

#endif // DESSIN_H
