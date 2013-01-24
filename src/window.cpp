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

Window::Window(QWidget *parent):QWidget(parent) {
    //init window styles 
    setWindowTitle(tr("media-player"));
    UI();
    setPlayer();
    
    connection();
}

bool Window::initWindow() {
    
    return true;
}

void Window::setPlayer() {
    _player = new Player();
    player = _player->getPlayer();
    playlist = _player->getPlaylist();
}

Player *Window::getPlayer() {
    return _player;
}

bool Window::initPlaylist(int argc, char **argv) {
    if(getPlayer() == NULL)
        return false;
    for(int i = 0; i < argc; i ++) {
        QFileInfo fileInfo(argv[i]);
        TagLib::FileRef file(fileInfo.absoluteFilePath().toUtf8());
        //QPixmap pix;
        if(!file.isNull()) {
            if(file.tag() == NULL || file.audioProperties() == NULL)
                continue;
            QTableWidgetItem *song = new QTableWidgetItem(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)));
            song->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            QTableWidgetItem *singer = new QTableWidgetItem(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true)));
            singer->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            /* add to playlist */ 
            int rowCount = taglistWidget->rowCount(); 
            taglistWidget->insertRow (rowCount);
            taglistWidget->setItem (rowCount, 0, song);
            taglistWidget->setItem (rowCount, 1, singer);
            
            playlist->addMedia(QUrl::fromLocalFile(QString::fromUtf8(argv[i])));
        }
    }
    if(!playlist->isEmpty()) {
        player->setPlaylist(playlist);
        // autoplay
        player->play();
    }
    //player->setVolume(5);
    return true;
}

void Window::UI() {
    //size
    setFixedSize(1000, 600);
    
    //layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);
    QVBoxLayout *vLLayout = new QVBoxLayout;
    QVBoxLayout *vRLayout = new QVBoxLayout;
    layout->addLayout(vLLayout);
    layout->addLayout(vRLayout);
    //videoWidget = new QVideoWidget(this);
    videoWidget = new QWidget(this);
    toolWidget = new QWidget(this);
    toolWidget->setFixedSize(720, 60);
    
    infoWidget = new QWidget(this);
    taglistWidget = new List(this);
    tabWidget = new QTabWidget(this);
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
//    mute->setCheckable(true);
//    mute->setChecked(false);
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
    vLayout->addSpacing(23);
    vLayout->addWidget(mute, 0);
    vLayout->addWidget(volume, 1);
    vLayout->addSpacing(10);
    vLayout->addWidget(title, 6, Qt::AlignVCenter | Qt::AlignHCenter);
    vLayout->addSpacing(10);
    vLayout->addWidget(lib, 0);
    vLayout->addSpacing(3);
    gLayout->addLayout(pLayout, 1, 2, 1, 10, Qt::AlignHCenter | Qt::AlignVCenter);
    gLayout->addLayout(vLayout, 2, 2, 1, 10, Qt::AlignHCenter | Qt::AlignVCenter);
    
    //slider actions
    process->setAcceptDrops(true);
    volume->setAcceptDrops(true);
    
    //right widgets
    vRLayout->addWidget(infoWidget);
    infoWidget->setFixedHeight(80);
    vRLayout->addWidget(tabWidget);
    tabWidget->addTab(taglistWidget, tr("默认列表"));
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
    connect(player, &QMediaPlayer::volumeChanged, [=](int val){
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
    //connect(tab, &QTabWidget::currentChanged)
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
            //QPixmap pix;
            if(file.isValid()) {
                this->title->setText(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName()) : tr(file.tag()->title().toCString(true)));
                //get attached picture
//                ID3v2::FrameList pictures = file.ID3v2Tag()->frameListMap()["APIC"];
//                if(!pictures.isEmpty()) {
//                    TagLib::ID3v2::AttachedPictureFrame *tmp = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(pictures.front());
//                    size_t size = tmp->picture().size();
//                    pix.loadFromData((const unsigned char *)tmp->picture().data(),size,"JPEG");
//                    pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//                    picture->setPixmap(pix);
//                }
//                else {
//                    pix.load(":/default.png","PNG");
//                    pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//                    picture->setPixmap(pix);
//                }
            }
            else {
                title->setText (tr("%1").arg (fileInfo.baseName()));
//                pix.load(":/default.png","PNG");
//                pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//                picture->setPixmap(pix);
            }
        }
//        else {
//            /*do nothing*/
//        }
}

void Window::closeEvent(QCloseEvent *event) {
    event->accept();
}
