#ifndef IMAGECLICKABLE_H
#define IMAGECLICKABLE_H
#include <QLabel>
#include <string>
class ImageClickable: public QLabel
{

    Q_OBJECT

public:
    explicit ImageClickable( std::string s, QWidget * parent = 0);
    ~ImageClickable();


signals:
    void clicked(std::string);

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
    std::string path;
};

#endif // IMAGECLICKABLE_H
