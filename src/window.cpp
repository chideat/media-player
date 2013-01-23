#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <fileref.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <apetag.h>

Window::Window(Player *player, QWidget *parent):QWidget(parent) {
    this->player = player->getPlayer();
    this->playlist = player->getPlaylist();
    setWindowTitle(tr("media-player"));
    UI();
    
    volume->setRange(0, 50);
    connection();
}

/**
 * @brief Window::init
 * @return 
 * load the necessary config from the config file
 * as 
 * themes
 * playlist
 */
bool Window::initWindow() {
    
    return true;
}

bool Window::initPlaylist(int argc, char **argv) {
    for(int i = 0; i < argc; i ++) {
        if(listWidget->addItem(argv[i])) {
            playlist->addMedia(QUrl::fromLocalFile(QString::fromUtf8(argv[i])));
        }
    }
    if(!playlist->isEmpty()) {
        player->setPlaylist(playlist);
        // autoplay
        player->play();
    }
    return true;
}

void Window::UI() {
    //size
    setFixedSize(1000, 600);
    
    //layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(3);
    
    QVBoxLayout *vLLayout = new QVBoxLayout;
    QVBoxLayout *vRLayout = new QVBoxLayout;
    layout->addLayout(vLLayout);
    layout->addLayout(vRLayout);
    //videoWidget = new QVideoWidget(this);
    videoWidget = new QWebView(this);
//    videoWidget->setFixedWidth(720);
//    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolWidget = new QWidget(this);
    toolWidget->setFixedSize(720, 60);
    
    infoWidget = new QWidget(this);
    listWidget = new List(this);
    listWidget->setFixedWidth(280);
    listWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuWidget = new QWidget(this);
    
    //widgets left
    vLLayout->addWidget(videoWidget);
    vLLayout->addWidget(toolWidget);

    
    //toolwidget
    QGridLayout *gLayout = new QGridLayout;
    gLayout->setSpacing(3);
    
    QHBoxLayout *RTLayout = new QHBoxLayout;
    toolWidget->setLayout(gLayout);
    previous = new QToolButton;
    previous->setIcon(QIcon(":/24x24/previous.png"));
    previous->setShortcut(QKeySequence("Ctrl+P"));
    previous->setIconSize(QSize(24, 24));
    previous->setStyleSheet ("QToolButton{border:0px;}");
    next = new QToolButton;
    next->setIcon(QIcon(":/24x24/next.png"));
    next->setShortcut(QKeySequence("Ctrl+N"));
    next->setIconSize(QSize(24, 24));
    next->setStyleSheet ("QToolButton{border:0px;}");
    play = new QToolButton;
    play->setIcon(QIcon(":/24x24/play.png"));
    play->setShortcut(QKeySequence("Ctrl+N"));
    play->setIconSize(QSize(24, 24));
    play->setStyleSheet ("QToolButton{border:0px;}");
    RTLayout->addWidget(previous);
    RTLayout->addWidget(play);
    RTLayout->addWidget(next);
    gLayout->addLayout(RTLayout, 1, 1, 2, 1, Qt::AlignBottom | Qt::AlignVCenter);
    
    previous->setCheckable(true);
    play->setCheckable(true);
    next->setCheckable(true);
    
    QHBoxLayout *pLayout = new QHBoxLayout;
    QHBoxLayout *vLayout = new QHBoxLayout;
    
    process = new QSlider(Qt::Horizontal, this);
    time = new QLabel("00:00");
    mute = new QToolButton(this);
    mute->setIcon(QIcon(":/16x16/volume-medium.png"));
    mute->setIconSize(QSize(16, 16));
    mute->setStyleSheet ("QToolButton {border:0;}");
    mute->setCheckable(true);
    mute->setChecked(true);
    isMuted = false;
    volume = new QSlider(Qt::Horizontal, this);
    title = new QLabel(tr("media-player"));
    lib = new QToolButton(this);
    lib->setIcon(QIcon(":/16x16/library.png"));
    lib->setIconSize(QSize(16, 16));
    lib->setStyleSheet("QToolButton {border:0;}");

    pLayout->setSpacing(0);
    vLayout->setSpacing(0);
    pLayout->addSpacing(20);
    pLayout->addWidget(process, 9);
    pLayout->addSpacing(3);
    pLayout->addWidget(time, 0);
    pLayout->addSpacing(10);
    pLayout->addWidget(lib, 0);
    vLayout->addSpacing(23);
    vLayout->addWidget(mute, 0);
    vLayout->addWidget(volume, 1);
    vLayout->addSpacing(10);
    vLayout->addWidget(title, 6, Qt::AlignVCenter | Qt::AlignHCenter);
    vLayout->addSpacing(10);
    gLayout->addLayout(pLayout, 1, 2, 1, 10, Qt::AlignHCenter | Qt::AlignVCenter);
    gLayout->addLayout(vLayout, 2, 2, 1, 10, Qt::AlignHCenter | Qt::AlignVCenter);
    
    //slider actions
    process->setAcceptDrops(true);
    volume->setAcceptDrops(true);
    
    
    //right widgets
    vRLayout->addWidget(infoWidget);
    infoWidget->setFixedHeight(80);
    vRLayout->addWidget(listWidget);
    //tabWidget->addTab(listWidget, tr("默认列表"));
    vRLayout->addWidget(menuWidget);
    menuWidget->setFixedHeight(45);
}

void Window::connection() {
    connect(player, &QMediaPlayer::positionChanged, this, &Window::setPorcessPosition);
    connect(process, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(player, &QMediaPlayer::currentMediaChanged, this, &Window::currentMediaChanged);
    connect(player, &QMediaPlayer::durationChanged, [=](qint64 duration){
        process->setRange(0, (int)duration);
    });
    connect(previous, &QToolButton::pressed, playlist, &QMediaPlaylist::previous);
    connect(next, &QToolButton::pressed, playlist, &QMediaPlaylist::next);
    connect(volume, &QSlider::sliderMoved, player, &QMediaPlayer::setVolume);
    connect(volume, &QSlider::sliderMoved, [=](int val){
        if(val >= 40)
            mute->setIcon(QIcon(":/16x16/volume-high.png"));
        else if(val >= 20)
            mute->setIcon(QIcon(":/16x16/volume-medium.png"));
        else if(val >= 5)
            mute->setIcon(QIcon(":/16x16/volume-low.png"));
        else 
            mute->setIcon(QIcon(":/16x16/volume-zero.png"));
    });
    connect(mute, &QToolButton::released, [=](){
        if(isMuted) {
            //mute->setChecked(false);
            isMuted = false;
            player->setMuted(false);
            mute->setIcon(icon);
        }
        else {
//            mute->setChecked(true);
            isMuted = true;
            player->setMuted(true);
            icon = mute->icon();
            mute->setIcon(QIcon(":/16x16/volume-muted.png"));
        }
    });
    connect(play, &QToolButton::released, [=](){
        if(isPlaying) {
            player->pause();
            isPlaying = false;
        }
        else {
            player->play();
            isPlaying = true;
        }
    });
    connect(player, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State newState){
        switch(newState) {
        case QMediaPlayer::PlayingState :
            play->setIcon(QIcon(":/24x24/pause.png"));
            isPlaying = true;
            break;
        case QMediaPlayer::PausedState:
        case QMediaPlayer::StoppedState:
            play->setIcon(QIcon(":/24x24/play.png"));
            isPlaying = false;
            break;
        }
    });
}

void Window::setPorcessPosition(qint64 val) {
//    if(val >= 2147483648)
//        process->setValue((int)val / 1000);
//    else 
        process->setValue((int)val);
        QTime displayTime(0,(val / 60000) % 60, (val / 1000) % 60);
        time->setText (displayTime.toString ("mm:ss"));
}

void Window::currentMediaChanged(const QMediaContent &media) {
    process->setValue(0);
    metaData(media.canonicalUrl());
}

void Window::metaData(QUrl url) {
    QString path = url.path();
    if(!path.isNull() && !path.isEmpty()){
            QFileInfo fileInfo(path);
            //here update the picture
            TagLib::MPEG::File file(fileInfo.absoluteFilePath().toUtf8());
            if(file.isValid()) {
                this->title->setText(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName()) : tr(file.tag()->title().toCString(true)));
            }
            else {
                title->setText (tr("%1").arg (fileInfo.baseName()));
            }
        }
}

void Window::closeEvent(QCloseEvent *event) {
    event->accept();
}
