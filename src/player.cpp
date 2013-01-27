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
    if(index < 0 && !player->playlist()->isEmpty()) 
        switch(player->state()) {
        case QMediaPlayer::StoppedState :
        case QMediaPlayer::PausedState:
            player->play();
        case QMediaPlayer::PlayingState:
            player->play();
        }
    else if(index >= 0) {
        playlist->setCurrentIndex(index);
        player->play();
    }
        

        
    //else if(index >= 0 && player->playlist()->)
}
