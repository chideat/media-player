#include "player.h"

/**
 * @brief Player::Player
 * @param parent
 */
Player::Player() {
    player = new QMediaPlayer(NULL);
    playlist = new QMediaPlaylist(NULL);
    player->setPlaylist(playlist);
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

void Player::play(int index) {
    if(index < 0 && !player->playlist()->isEmpty()) {
        switch(player->state()) {
        case QMediaPlayer::StoppedState :
        case QMediaPlayer::PausedState:
            player->play();
            break;
        case QMediaPlayer::PlayingState:
            player->pause();
            break;
        }
    }
    else if(index >= 0) {
        if(index != playlist->currentIndex()) 
            playlist->setCurrentIndex(index);
        else 
            player->stop();
        player->play();
    }
}
