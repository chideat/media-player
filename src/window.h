#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QToolButton>
#include <QSlider>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtWebKit/QWebView>
#include "player.h"
#include "list.h"


class Window : public QWidget {
    Q_OBJECT
public: 
    Window(Player *player, QWidget *parent = NULL);
    bool initWindow();
    bool initPlaylist(int argc, char **argv);

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    
    QWidget *toolWidget, *menuWidget, *infoWidget;
    QWebView *videoWidget;
    List *listWidget;
    QTabWidget *tabWidget; 
    //QVideoWidget *videoWidget;
    
    QToolButton *previous;
    QToolButton *next;
    QToolButton *play;
    /*tmp*/
    bool isPlaying;
    
    /*tmp*/
    bool isMuted;
    QIcon icon;
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
    void metaData(QUrl url);
    void closeEvent(QCloseEvent *);
};

#endif // WINDOW_H
