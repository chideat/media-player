#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Player {
public : 
    Player();
//    Player(QString path, QObject *parent = NULL);
//    Player(QStringList paths, QObject *parent = NULL);
    
    QMediaPlayer *player ;
    QMediaPlaylist *playlist;
    
    void initPlayer(int volume = 0);
    QMediaPlayer *getPlayer();
    QMediaPlaylist *getPlaylist();
};


#endif // PLAYER_H
