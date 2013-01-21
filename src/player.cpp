#include "player.h"

/**
 * @brief Player::Player
 * @param parent
 */
Player::Player() {
    player = new QMediaPlayer(NULL);
    playlist = new QMediaPlaylist(NULL);
    player->setPlaylist(playlist);
    
    initPlayer();
}

/**
 * @brief Player::Player
 * @param parent
 * @param path
 * @problems how to play a media from path
 */
//Player::Player(QString path, QObject *parent) : Player(parent){
//    /* apperent just support local file */
//    player->setMedia(QUrl::fromLocalFile(path));
//    /* the default action is play */
//    player->play();
//}

/* load medias */
//Player::Player(QStringList paths, QObject *parent):Player(parent) {
//    foreach(QString path, paths)
//        playlist->addMedia(QUrl::fromLocalFile(path));
//    player->setPlaylist(playlist);
//    player->play();
//}

/* give up load the play history */
void Player::initPlayer(int volume) {
    player->setVolume(volume);
}

QMediaPlayer* Player::getPlayer()  {
    if(player == NULL)
        player = new QMediaPlayer(NULL);
    return player;
}

QMediaPlaylist *Player::getPlaylist() {
    if(playlist == NULL)
        playlist = new QMediaPlaylist(NULL);
    return playlist;
}

