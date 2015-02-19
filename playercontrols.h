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

public slots:
    void setState(QMediaPlayer::State state);

signals:
    void play();
    void pause();
    void stop();

private slots:
    void playClicked();
    void replay_inf();

private:
    QMediaPlayer::State playerState;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
    QAbstractButton *replayButton;

    bool choix_replay;
};

#endif // PLAYERCONTROLS_H
