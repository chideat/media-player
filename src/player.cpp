#include "player.h"

/**
 * @brief Player::Player
 * @param parent
 */
Player::Player() {
    player = new QMediaPlayer(NULL);
    playlist = new QMediaPlaylist(NULL);
    //player->setPlaylist(playlist);
    initPlayer();
}

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

