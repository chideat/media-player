#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

#define MAX_VOLUME 50

class Player {
public : 
    Player();
    
    QMediaPlayer *player ;
    QMediaPlaylist *playlist;
    
    void initPlayer(int volume = 5);
    QMediaPlayer *getPlayer();
    QMediaPlaylist *getPlaylist();
    void play(int index);
};


#endif // PLAYER_H
