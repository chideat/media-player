#ifndef WINDOW_H
#define WINDOW_H


#include <QWidget>
#include <QToolButton>
#include <QSlider>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include "player.h"

class Window : public QWidget {
    Q_OBJECT
public: 
    Window(QWidget *parent = NULL);
    void setPlayer(Player *player);
    bool initWindow();
    bool initPlaylist(int argc, char **argv);
private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    
    QWidget *videoWidget, *toolWidget, *taglistWidget, *tabWidget, *menuWidget;
    //QVideoWidget *videoWidget;
    
    QToolButton *previous;
    QToolButton *next;
    QToolButton *play;
    
    QToolButton *mute;
    QSlider *volume;
    QSlider *process;
    
    
    
    
    
    void UI();
};

#endif // WINDOW_H
