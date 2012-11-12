#ifndef DOWN_H
#define DOWN_H

#include "types.h"
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QMenuItem>
#include <QAction>

class Down : public QWidget {
    Q_OBJECT
public :
    Down(QWidget *parent = NULL);
private :
    //gui
    QPushButton *addMusicButton;
    QPushButton *delMusicButton;
    QPushButton *playModelButton;
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
    //model
    QAction *playSingal;
    QAction *playRepeatSingal;
    QAction *playAll;
    QAction *playRepeatAll;
    QAction *playShuffle;

    void initConnection();

public slots:
    void addFileSlot();
    void addDirSlot();
    void delCurrentSlot();
    void delSelectionSlot();
    void delAllSlot();
    void playSingalSlot();
    void playAllSlot();
    void playRepeatSingalSlot();
    void playRepeatAllSlot();
    void playShuffleSlot();

signals :
    void load(LoadType type,QString path);
    void deleteWhat(qint8 kind);
    void playModel(Model model);
};
#endif // DOWN_H
