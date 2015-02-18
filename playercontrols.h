#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>
#include <QAbstractButton>
#include <QComboBox>


class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    PlayerControls(QWidget *parent = 0);
    ~PlayerControls();
    QMediaPlayer::State state() const;
    qreal playbackRate() const;

public slots:
    void setState(QMediaPlayer::State state);
    void setPlaybackRate(float rate);

signals:
    void play();
    void pause();
    void stop();
    void changeRate(qreal rate);

private slots:
    void playClicked();
    void updateRate();

private:
    QMediaPlayer::State playerState;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
    QAbstractButton *replay;

    QComboBox *rateBox;
};

#endif // PLAYERCONTROLS_H
