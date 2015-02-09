#include "accueil.h"
#include <QVBoxLayout>

Accueil::Accueil(QWidget *parent):QMainWindow(parent)
{
    longueur = 1050;
    largeur = 740;
    this->setWindowTitle("Accueil");
    this->setMinimumSize(longueur,largeur);
    this->setMaximumSize(longueur,largeur);

    label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Pas de projet ouvert");
    label->setGeometry(QRect(500, 350, 150, 20));
    QLabel *label1=new QLabel;
    label1->setPixmap( QPixmap( "/comptes/E106407K/Chat.jpg" ) );
    //label1->setGeometry(20,20);
    label1->adjustSize();
    label1->setScaledContents(true);
    QLabel *label2=new QLabel;
    label2->setPixmap( QPixmap( "/comptes/E106407K/Chat2.jpg" ) );
    QLabel *label3=new QLabel;
    label3->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label4=new QLabel;
    label4->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label5=new QLabel;
    label5->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label6=new QLabel;
    label6->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label7=new QLabel;
    label7->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label8=new QLabel;
    label8->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label9=new QLabel;
    label9->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label10=new QLabel;
    label10->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label11=new QLabel;
    label11->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );
    QLabel *label12=new QLabel;
    label12->setPixmap( QPixmap( "/comptes/E106407K/Chat3.jpg" ) );

    QScrollArea *scrollarea = new QScrollArea(this);

    QVBoxLayout *test = new QVBoxLayout();
    test->addWidget(label3);
    test->addWidget(label2);
    test->addWidget(label4);
    test->addWidget(label5);
    test->addWidget(label6);
    test->addWidget(label7);
    test->addWidget(label8);
    test->addWidget(label9);
    test->addWidget(label11);
    test->addWidget(label12);
    test->addWidget(label10);
    test->addWidget(label1);
    ma = new QWidget(this);
    ma->setLayout(test);

    scrollarea->setWidget(ma);
    scrollarea->setGeometry(0, 0, 500, 500);
    //ma->setGeometry(0, 0, 500, 500);
    nouveau_projet = new QPushButton("Nouveau projet", this);
    nouveau_projet->setGeometry(500, 400, 150, 50);

    charger_projet = new QPushButton("Charger projet", this);
    charger_projet->setGeometry(500, 450, 150, 50);

    connect(nouveau_projet, SIGNAL(clicked()), this, SLOT(ouvrir_projet()));
}

Accueil::~Accueil()
{
}

void Accueil::ouvrir_projet(){

    delete(charger_projet);
    delete(nouveau_projet);
    delete(label);

}

