#ifndef IMAGECLICKABLE_H
#define IMAGECLICKABLE_H
#include <QLabel>
#include <string>
class ImageClickable: public QLabel
{

    Q_OBJECT

public:
    explicit ImageClickable(std::string s, int index, QWidget * parent = 0);
    ~ImageClickable();
    std::string get_path();
    std::string get_path2();
    void set_path2(std::string p2);
    void changer_image(QString img);


signals:
    void clicked(std::string,std::string, int);

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
    std::string path;
    std::string path2;
    int index;
};

#endif // IMAGECLICKABLE_H
