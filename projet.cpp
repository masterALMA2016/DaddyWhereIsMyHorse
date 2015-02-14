#include "projet.h"

Projet::Projet(int x, int y, QWidget *parent):QMainWindow(parent)
{
    //parametrage fenetre
    longueur_fenetre = x;
    largeur_fenetre = y;

    this->setWindowTitle("Projet");
    this->setMinimumSize(longueur_fenetre,largeur_fenetre);
    this->setMaximumSize(longueur_fenetre,largeur_fenetre);




    barre_menu = new QMenuBar(this);
    setMenuBar(barre_menu);
    barre_menu->setVisible(true);
    QMenu *fichier = new QMenu("fichier");
    barre_menu->addMenu(fichier);
    QAction *ac = new QAction(this);
    ac->setText(QString::fromUtf8("fermer"));
    ac->setShortcut(QKeySequence("CTRL+Q"));
    connect(ac, SIGNAL(triggered()), this, SLOT(close()));
    fichier->addAction(ac);

    dessin_courant = new Dessin(this);
    dessin_courant->setGeometry(500, 500,200,200);

    //ajout boutons

    //pour la couleur du crayon
    couleur = new QPushButton(this);
    couleur->setGeometry(longueur_fenetre-100, barre_menu->geometry().height() ,40 ,30);
    connect(couleur, SIGNAL(clicked()), this, SLOT(changer_couleur()));

    //pour utiliser le crayon
    QPushButton *crayon = new QPushButton(this);
    crayon->setGeometry(longueur_fenetre-50, barre_menu->geometry().height(), 50, 50);
    QPixmap icone("../DaddyWhereIsMyHorse/crayon.png");
    icone = icone.scaledToWidth(40, Qt::FastTransformation);
    QIcon i(icone);
    crayon->setIcon(i);
    crayon->setIconSize(icone.rect().size());

    //pour utiliser la gomme
    QPushButton *gomme = new QPushButton(this);
    gomme->setGeometry(longueur_fenetre-150, barre_menu->geometry().height(), 50, 50);
    QPixmap icone_gomme("../DaddyWhereIsMyHorse/gomme.png");
    icone_gomme = icone_gomme.scaledToWidth(40, Qt::FastTransformation);
    QIcon i2(icone_gomme);
    gomme->setIcon(i2);
    gomme->setIconSize(icone.rect().size());

    QScrollArea *scrollarea_zone_images = new QScrollArea(this);
    QVBoxLayout *layout_zone_images = new QVBoxLayout();


    for(int i=0; i<10; i++){
        ImageClickable *image=new ImageClickable("/home/Soge/Images/Wallpapers/game_of_thrones_016.jpg");
        layout_zone_images->addWidget(image);
        mes_images.push_back(image);
    }

    zone_images = new QWidget(this);
    zone_images->setLayout(layout_zone_images);
    scrollarea_zone_images->setWidget(zone_images);
    scrollarea_zone_images->setGeometry(0, barre_menu->geometry().y()+barre_menu->height(), 205, largeur_fenetre-barre_menu->geometry().height());

}

Projet::~Projet()
{

}

void Projet::changer_couleur(){
        QColor col = QColorDialog::getColor(Qt::black, this, "Select Color");
        couleur->setStyleSheet("background-color:"+col.name()+";");
        dessin_courant->set_color(col);
}
