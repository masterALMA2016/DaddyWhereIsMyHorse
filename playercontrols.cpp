#include "playercontrols.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <iostream>
PlayerControls::PlayerControls(QWidget *parent): QWidget(parent), playerState(QMediaPlayer::StoppedState), playButton(0), stopButton(0)
{
    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    choix_replay = true;

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);

    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

    replayButton = new QToolButton(this);
    replayButton->setEnabled(true);
    QPixmap image_replay("../DaddyWhereIsMyHorse/replay.png");
    QIcon icone_replay(image_replay);
    replayButton->setIcon(icone_replay);
    replayButton->setDown(choix_replay);

    connect(replayButton, SIGNAL(clicked()), this, SLOT(replay_inf()));

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(stopButton);
    layout->addWidget(playButton);
    layout->addWidget(replayButton);
    setLayout(layout);
}

PlayerControls::~PlayerControls(){
    delete(playButton);
    delete(stopButton);
    delete(replayButton);
}

QMediaPlayer::State PlayerControls::state() const
{
    return playerState;
}

void PlayerControls::setState(QMediaPlayer::State state)
{
    if (state != playerState ) {

        switch (state) {
        case QMediaPlayer::StoppedState :

            stopButton->setEnabled(false);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            playerState = state;
            if(choix_replay){
                setState(QMediaPlayer::PlayingState);
                emit play();
            }
            break;
        case QMediaPlayer::PlayingState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            playerState = state;

            break;
        case QMediaPlayer::PausedState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            playerState = state;

            break;
        }
    }
}


void PlayerControls::playClicked()
{    switch (playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }
}

void PlayerControls::replay_inf(){
    choix_replay = !choix_replay;
    replayButton->setDown(choix_replay);
}
