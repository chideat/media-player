#include "window.h"
#include <QVBoxLayout>
#include <QDockWidget>
#include <QCloseEvent>

Window::Window(QWidget *parent) : QWidget(parent) {
    setWindowIcon (QIcon(":/lMusic.png"));
    initTrayIcon();

    up = new Up(this);
    tab = new Tab(this);
    down = new Down(this);
    load = new Load(this);

    initTrayIconMenu ();
    initLayout ();
    initConnect ();
    setFixedSize (345,550);
}

void Window::initTrayIcon () {
    trayIcon = new QSystemTrayIcon(QIcon(":/lMusic.png"),this);
    trayIcon->setToolTip (tr("lMusic丰富你的Linux生活"));
    trayIcon->show ();
}

void Window::initLayout () {
    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->setMargin (0);
    boxLayout->setSpacing (0);
    //up->setMinimumHeight (100);
    boxLayout->addWidget (up);
    //list->setMaximumHeight (320);
    boxLayout->addWidget (tab);
    down->setMaximumHeight (30);
    boxLayout->addWidget (down);
    setLayout (boxLayout);
}

void Window::setLoad(LoadType type, QString path) {
    load->setLoadType(type);
    load->setPath(path);
    load->start();
    load->wait();
    //exti automatically
    qDebug()<<"load setLoad";
}

void Window::initConnect () {
    //up -- list
    connect(up,SIGNAL(next()),tab->getList(0),SLOT(next()));
    connect(up,SIGNAL(previous()),tab->getList(0),SLOT(previous()));

    //list -- up
    connect(tab->getList(0),SIGNAL(jump(QString)),up,SLOT(update(QString)));
    //connect(tab->getList(0),SIGNAL(next(QString)),up,SLOT(enqueue(QString)));

    //this(load) -- list
    connect(load,SIGNAL(newItem(Music*)),tab->getList(0),SLOT(addItem(Music*)));

    //down -- load
    connect(down,SIGNAL(load(LoadType,QString)),this,SLOT(setLoad(LoadType,QString)));

    //down -- list
    connect(down,SIGNAL(playModel(Model)),tab->getList(0),SLOT(modelChanged(Model)));
    connect(down,SIGNAL(deleteWhat(qint8)),tab->getList(0),SLOT(deleteWhat(qint8)));

    connect(quit,SIGNAL(triggered()),this,SLOT(quitSlot()));
    connect (trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconActived(QSystemTrayIcon::ActivationReason)));
    connect(showOrHidden,SIGNAL(triggered()),this,SLOT(showOrHiddenSlot()));
    connect(previous,SIGNAL(triggered()),up,SLOT(ePrevious()));
    connect(playOrPause,SIGNAL(triggered()),up,SLOT(ePlay()));
    connect(next,SIGNAL(triggered()),up,SLOT(eNext()));
    connect(modelSingal,SIGNAL(triggered()),down,SLOT(playSingalSlot()));
    connect(modelAll,SIGNAL(triggered()),down,SLOT(playAllSlot()));
    connect(modelRepeatSingal,SIGNAL(triggered()),down,SLOT(playRepeatSingalSlot()));
    connect(modelRepeatAll,SIGNAL(triggered()),down,SLOT(playRepeatAllSlot()));
    connect(modelShuffle,SIGNAL(triggered()),down,SLOT(playShuffleSlot()));
}

void Window::initTrayIconMenu () {
    trayIconMenu = new QMenu(this);
    showOrHidden = trayIconMenu->addAction (tr("显示/隐藏"));
    trayIconMenu->addSeparator ();
    previous = trayIconMenu->addAction (QIcon(":/16x16/previous.png"),tr("前一个"));
    previous->setShortcut (QKeySequence("Ctrl+Up"));
    playOrPause = trayIconMenu->addAction (QIcon(":/16x16/play.png"),tr("播放/暂停"));
    playOrPause->setShortcut (QKeySequence("Ctrl+P"));
    next = trayIconMenu->addAction (QIcon(":/16x16/next.png"),tr("下一个"));
    next->setShortcut (QKeySequence("Ctrl+Down"));
    trayIconMenu->addSeparator ();
    model = new QMenu(tr("模式"));
    modelSingal = model->addAction (tr("单曲播放"));
    modelAll = model->addAction (tr("全部播放"));
    modelRepeatSingal = model->addAction (tr("单曲循环"));
    modelRepeatAll = model->addAction (tr("循环全部"));
    modelShuffle = model->addAction (tr("随机播放"));
    trayIconMenu->addMenu (model);
    trayIconMenu->addSeparator ();
    preference = trayIconMenu->addAction (tr("设置"));
    quit = trayIconMenu->addAction (QIcon(":/16x16/shutdown.png"),tr("退出"));
    quit->setShortcut (QKeySequence::Quit);
    about = trayIconMenu->addAction (tr("关于GMusic"));

    trayIcon->setContextMenu (trayIconMenu);
}

void Window::closeEvent (QCloseEvent *event) {
    trayIcon->showMessage (tr("GMusic"), tr("GMusic丰富你的Linux生活"),QSystemTrayIcon::Information,7000);
    this->hide ();
    event->ignore ();
}

void Window::trayIconActived (QSystemTrayIcon::ActivationReason reason) {
    switch(reason) {
    case QSystemTrayIcon::Trigger : {
        if(this->isHidden ())
            this->show ();
        else
            this->hide ();
        break;
    }
    case QSystemTrayIcon::Context: 
    case QSystemTrayIcon::Unknown:
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::MiddleClick:
    {
        break;
    }
    }
}

void Window::showOrHiddenSlot () {
    if(this->isHidden ())
        this->show ();
    else {
        this->hide ();
    }
}

void Window::quitSlot () {
        //here write the date  
     exit (0);
}