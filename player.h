#ifndef PLAYER_H
#define PLAYER_H


#include <QMediaPlayer>
#include <videowidget.h>
#include <QLabel>
#include <QVideoProbe>
#include <QString>
#include <QSlider>
#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QMediaMetaData>
#include <QtWidgets>
#include "playercontrols.h"
#include "videowidget.h"


class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QString chemin_video, QWidget *parent = 0);
    ~Player();

private slots:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void seek(int seconds);

signals:
    void dest();

protected:
    void closeEvent(QCloseEvent*);

private:
    void updateDurationInfo(qint64 currentInfo);

    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QSlider *slider;
    QLabel *labelDuration;
    qint64 duration;
};

#endif
