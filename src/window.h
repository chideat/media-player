#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QTableWidget>
#include <QAction>
#include <QPushButton>
#include <QMenu>
#include "list.h"
#include "load.h"
#include "tab.h"
#include "up.h"
#include "down.h"

class Up;
class List;
//without menu
/*
at the top of the player
        the seekSlider
        volumeSlider
        lcd
        name
*/
class Window : public QWidget {
    Q_OBJECT
public :
    Window(QWidget *parent=NULL);
private :
    Up *up;
    Tab *tab;
    Down *down;
    Load *load;
    //seekslide
    //SeekSlider类别提供一个可滑动的slider来设定多媒体串流播放的位置。
    //所以它会连接到MediaObject，并控制串流目前的位置。
    //seekSlider->setMediaObject (mediaObject);
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *showOrHidden;
    QAction *previous;
    QAction *playOrPause;
    QAction *stop;
    QAction *next;
    QMenu *model;
    QAction *modelSingal;
    QAction *modelRepeatSingal;
    QAction *modelRepeatAll;
    QAction *modelAll;
    QAction *modelShuffle;
    QAction *preference;
    QAction *quit;
    QAction *about;

    void initTrayIcon();
    void initTrayIconMenu();
    void initLayout();
    void initConnect();
protected :
    void closeEvent (QCloseEvent *);
public slots:
    void setLoad(LoadType type, QString path);
    void showOrHiddenSlot();
    void trayIconActived(QSystemTrayIcon::ActivationReason reason);
    void quitSlot();
};

#endif // WINDOW_H
