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
    Window(Player *player, QWidget *parent = NULL);
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
    QLabel *time;
    QLabel *title;
    QToolButton *lib;
    
    void connection();
    void UI();
public slots:
    void setPorcessPosition(qint64 val);
    void currentMediaChanged(const QMediaContent &media);
    
};

#endif // WINDOW_H
