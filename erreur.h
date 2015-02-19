#ifndef ERREUR_H
#define ERREUR_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class Erreur: public QDialog
{
        Q_OBJECT

public:
    Erreur(QWidget * parent = 0);
    ~Erreur();
};

#endif // ERREUR_H
