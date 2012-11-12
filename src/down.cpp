
#include "down.h"
#include <QDebug>
#include <QGridLayout>
#include <QFileDialog>
#include <QDesktopServices>

Down::Down(QWidget *parent) :QWidget(parent) {
    addMusicButton = new QPushButton(QIcon(":/16x16/add.png"),tr("添加"),this);
    delMusicButton = new QPushButton(QIcon(":/16x16/del.png"),tr("删除"),this);
    playModelButton = new QPushButton(QIcon(":/16x16/default.png"),tr("模式"),this);
    addMusicButton->setMouseTracking (false);
    delMusicButton->setMouseTracking (false);
    addMusicButton->setFocusPolicy (Qt::NoFocus);
    delMusicButton->setFocusPolicy (Qt::NoFocus);
    playModelButton->setFocusPolicy (Qt::NoFocus);

    //add
    addMusicMenu = new QMenu;
    addFile = addMusicMenu->addAction (tr("添加文件"));
    addDir = addMusicMenu->addAction (tr("添加目录"));
    //del
    delMusicMenu = new QMenu;
    delCurrent = delMusicMenu->addAction (tr("删除当前"));
    delSelection = delMusicMenu->addAction (tr("删除选中文件"));
    delAll = delMusicMenu->addAction (tr("清空播放列表"));
    //play
    playModelMenu = new QMenu;
    playSingal = playModelMenu->addAction (tr("播放单曲"));
    playAll = playModelMenu->addAction (tr("播放全部"));
    playRepeatSingal = playModelMenu->addAction (tr("单曲循环"));
    playRepeatAll = playModelMenu->addAction (tr("循环全部"));
    playShuffle = playModelMenu->addAction (tr("随机播放"));

    addMusicButton->setMenu (addMusicMenu);
    delMusicButton->setMenu (delMusicMenu);
    playModelButton->setMenu (playModelMenu);

    addMusicButton->setStyleSheet("QPushButton{border:0px;min-width: 5em;padding: 0px;}");
    delMusicButton->setStyleSheet("QPushButton{border:0px;min-width: 5em;padding: 0px;}");
    playModelButton->setStyleSheet("QPushButton{border:0px;min-width: 5em;padding: 0px;}");

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setMargin (0);
    gridLayout->setSpacing (0);
    gridLayout->addWidget (addMusicButton,1,1,1,1,Qt::AlignCenter | Qt::AlignVCenter);
    gridLayout->addWidget (delMusicButton,1,2,1,1,Qt::AlignCenter | Qt::AlignVCenter);
    gridLayout->addWidget (playModelButton,1,3,1,1,Qt::AlignCenter | Qt::AlignVCenter);

    setFixedHeight (30);


    //load
    initConnection ();
}


void Down::initConnection () {
    connect (addFile,SIGNAL(triggered()),this,SLOT(addFileSlot()));
    connect (addDir,SIGNAL(triggered()),this,SLOT(addDirSlot()));
    connect (delCurrent,SIGNAL(triggered()),this,SLOT(delCurrentSlot()));
    connect (delSelection,SIGNAL(triggered()),this,SLOT(delSelectionSlot()));
    connect (delAll,SIGNAL(triggered()),this,SLOT(delAllSlot()));
    connect (playSingal,SIGNAL(triggered()),this,SLOT(playSingalSlot()));
    connect (playAll,SIGNAL(triggered()),this,SLOT(playAllSlot()));
    connect (playRepeatSingal,SIGNAL(triggered()),SLOT(playRepeatSingalSlot()));
    connect (playRepeatAll,SIGNAL(triggered()),SLOT(playRepeatAllSlot()));
    connect (playShuffle,SIGNAL(triggered()),SLOT(playShuffleSlot()));
}

void Down::addFileSlot () {
    QString file = QFileDialog::getOpenFileName (NULL, tr("Select Musics ..."), QDesktopServices::storageLocation (QDesktopServices::MusicLocation)
                                                 , tr("Music Files (*.mp3);;All Files (*.*)"));
    emit load(LOAD_FILE,file);
}

void Down::addDirSlot () {
    QString dir = QFileDialog::getExistingDirectory (NULL, tr("Select a Folder ..."),
                                                     QDesktopServices::storageLocation (QDesktopServices::MusicLocation));
    emit load(LOAD_DIR,dir);
}

void Down::delCurrentSlot () {
    emit deleteWhat(0);
}

void Down::delSelectionSlot() {
    emit deleteWhat(1);
}

void Down::delAllSlot () {
    emit deleteWhat(-1);
}

void Down::playSingalSlot () {
    playModelButton->setIcon(QIcon(":/16x16/singal.png"));
    emit playModel(SINGAL);
}

void Down::playAllSlot () {
    playModelButton->setIcon(QIcon(":/16x16/default.png"));
    emit playModel (DEFAULT);
}

void Down::playRepeatSingalSlot () {
    playModelButton->setIcon(QIcon(":/16x16/repeatsingal.png"));
    emit playModel (REPEAT_SINGAL);
}

void Down::playRepeatAllSlot () {
    playModelButton->setIcon(QIcon(":/16x16/repeat.png"));
    emit playModel (REPEAT_ALL);
}

void Down::playShuffleSlot () {
    playModelButton->setIcon(QIcon(":/16x16/shuffle.png"));
    emit playModel (SHUFFLE);
}
