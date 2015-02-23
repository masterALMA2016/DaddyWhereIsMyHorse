#ifndef CREERPROJET_H
#define CREERPROJET_H

#include <QDialog>
#include <string>
#include <QPushButton>
#include <QInputDialog>
#include <QDir>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QDirIterator>
#include <QFileDialog>

class CreationProjet: public QDialog
{
    Q_OBJECT

public:
    explicit CreationProjet(QWidget * parent = 0);
    ~CreationProjet();

public slots:
    void envoyer_informations();
    void parcourir_dossier();
    void parcourir_video();

signals:
    void information_projet(QString chemin_projet, QString frequence);

private:
    QLineEdit *nom_projet;
    QLineEdit *chemin_video;
    QComboBox *choix_frequence;
    QLineEdit *chemin_projet;
    QLabel *probleme_chemin_projet;
    QLabel *probleme_nom_projet;
    QLabel *probleme_chemin_video;
};

#endif // CREERPROJET_H
