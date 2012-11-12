#include "player.h"


Player::Player(QWidget *parent) : QObject(parent){
    this->parent = parent;

    mediaObject = new Phonon::MediaObject;
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,parent);
    seekSlider = new Phonon::SeekSlider(mediaObject,parent);
    volumeSlider = new Phonon::VolumeSlider(audioOutput,parent);

    Phonon::createPath(mediaObject,audioOutput);

    //config(default)
    seekSlider->setTracking(true);
    seekSlider->setIconVisible(false);
    seekSlider->setMouseTracking(true);
    volumeSlider->setTracking(true);


    //connect
    connect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(eTick(qint64)));
    connect(mediaObject,SIGNAL(finished()),this,SLOT(eFinished()));
    connect(mediaObject,SIGNAL(stateChanged(Phonon::State,Phonon::State)),this,SLOT(eStateChanged(Phonon::State,Phonon::State)));
}

bool Player::play(QString path) {
    //start or stop
    if(path.isNull() || path.isEmpty()) {
        if(mediaObject->state() == Phonon::PlayingState)
            mediaObject->pause();
        else if(mediaObject->state() == Phonon::PausedState)
            mediaObject->play();
        else
            emit finished(NULL);
    }
    else {
        //do nothing
        mediaObject->stop();
        Phonon::MediaSource source(path);
        mediaObject->setCurrentSource(source);
        mediaObject->play();
    }
    return true;
}

bool Player::pause() {

    return true;
}


Phonon::State Player::getState() {
    return mediaObject->state();
}

Phonon::SeekSlider *Player::getSeekSlider() {
    return seekSlider;
}

Phonon::VolumeSlider *Player::getVolumeSlider() {
    return volumeSlider;
}

void Player::setTickInterval(qint64 interval) {
    mediaObject->setTickInterval(interval);
}

void Player::setVolume(double volume) {
    audioOutput->setVolume(volume);
}

void Player::setName(QString name) {
    audioOutput->setName(name);
}

void Player::eTick(qint64 tick) {
    emit this->tick(tick);
}

void Player::eFinished() {
    emit finished(NULL);
}

void Player::eStateChanged(Phonon::State newstate, Phonon::State /*oldstate*/) {
    emit stateChanged(newstate);
}
