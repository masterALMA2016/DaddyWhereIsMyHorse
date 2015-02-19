#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

class Preferences: public QDialog
{
        Q_OBJECT

public:
    explicit Preferences(int new_nb_pelures_doignons, int new_frequences_pelures_doignons, int new_previsualisation, bool new_image_fond, QWidget * parent = 0);
    ~Preferences();

signals:
    void information_projet(int new_nb_pelures_doignons, int new_frequences_pelures_doignons, int new_previsualisation, bool new_image_fond);

public slots:
    void envoyer_maj();

private:
    QLineEdit *nb_pelure_doignons;
    QComboBox *choix_frequence_pelures_doignons;
    QLineEdit *previsualisation_rapide;
    QCheckBox *image_de_fond;
};

#endif // PREFERENCES_H
