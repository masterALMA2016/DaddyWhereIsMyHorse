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

class CreationProjet: public QDialog
{
    Q_OBJECT

public:
    explicit CreationProjet(QWidget * parent=0);
    ~CreationProjet();

public slots:
    void envoyer_informations();

signals:
    void information_projet(std::string nom_projet, std::string chemin_projet, std::string chemin_video, std::string frequence);

private:

};

#endif // CREERPROJET_H
