/*
  this class deals with the attached picture, slider, privious and next and start and stop button


  */

#ifndef UP_H
#define UP_H

#include <QWidget>
#include <QFileInfo>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QLabel>
#include <QMutex>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>
#include "player.h"

class Up : public QWidget  {
    Q_OBJECT
public :
    Up(QWidget *parent);
private :
    void initPlayer();
    void initGui();
    void initConnect();
    void layout();
    //同步
    QMutex *mutex;
    //player
    Player *player;
    Phonon::SeekSlider *seekSlider;
    Phonon::VolumeSlider *volumeSlider;


    QLabel *title;
    QLabel *time;
    QLabel *picture;

    //component
    QToolButton *buttonPlayOrPause;
    QToolButton *buttonStop;
    QToolButton *buttonPrevious;
    QToolButton *buttonNext;
    QToolButton *buttonAddLocal;
    //actions
    QAction *actionPlayOrPause;//play or pause
    QAction *actionPrevious;
    QAction *actionNext;
public slots:
    //player
    void tick(qint64 tick);
    void ePrevious();
    void ePlay();
    void eNext();

    //gui
    void update(QString path);
    void stateChanged(Phonon::State newstate);
signals:
    void next();
    void previous();
};

#endif // UP_H
