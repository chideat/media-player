#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenu>
#include <QToolButton>

class Menu : public QWidget {
    Q_OBJECT
public : 
    QToolButton *add;
    QToolButton *del;
    QToolButton *mode;
    QMenu *addMusicMenu;
    QMenu *delMusicMenu;
    QMenu *playModelMenu;
    
    //add
    QAction *addFile;
    QAction *addDir;
    //del
    QAction *delCurrent;
    QAction *delSelection;
    QAction *delAll;
    //mode
    QAction *modeCurrentItemOnce;
    QAction *modeCurrentItemInLoop;
    QAction *modeSequential;
    QAction *modeLoop;
    QAction *modeRandom;
    
//CurrentItemOnce, CurrentItemInLoop, Sequential, Loop, Random 
};

#endif // MENU_H
