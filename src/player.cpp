#include "player.h"
#include <stdio.h>
#include <QUrl>
/**
 * @brief Player::Player
 * @param parent
 */
Player::Player(QObject *parent) {
    this->parent = parent;
    player = new QMediaPlayer(parent);
    playlist = new QMediaPlaylist(parent);
    
    initPlayer();
}

/**
 * @brief Player::Player
 * @param parent
 * @param path
 * @problems how to play a media from path
 */
Player::Player(QObject *parent, QString path) : Player(parent){
    /* apperent just support local file */
    player->setMedia(QUrl::fromLocalFile(path));
    /* the default action is play */
    player->play();
}

Player::Player(QObject *parent, QStringList paths):Player(parent) {
    
}

void Player::initPlayer(int volume) {
    player->setVolume(volume);
}

static QMediaPlayer* Player::getPlayer() {
    if(player == NULL)
        player = new QMediaPlayer(parent);
    return player;
}

static QMediaPlaylist* Player::getPlaylist() {
    if(playlist == NULL)
        playlist = new QMediaPlaylist(parent);
    return playlist;
}
 
