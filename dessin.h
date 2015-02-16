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
    explicit Dessin(int longueur, int largeur, QWidget * parent=0);
    ~Dessin();
    void set_color(QColor couleur);
    QColor get_color();
    void changer_taille_crayon(int i);
    void set_t(bool choix);
    void save(QString chemin);
    QPixmap get_image();

signals:
    void clicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();

private:
    QPen crayon;
    QPixmap dessin;
    bool trace;
    bool utiliser_crayon;
    int x;
    int y;


};

#endif // DESSIN_H
