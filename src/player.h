#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Player {
public : 
    QObject *parent;
    Player(QObject *parent);
    Player(QObject *parent, QString path);
    Player(QObject *parent, QStringList paths);
    
    QMediaPlayer *player ;
    QMediaPlaylist *playlist;
    
    void initPlayer(int volume = 30);
    static QMediaPlayer *getPlayer() const;
    static QMediaPlaylist *getPlaylist() const;
};


#endif // PLAYER_H
