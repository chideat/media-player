#include "window.h"
#include <QVBoxLayout>
#include <QByteArray>

Window::Window(QWidget *parent):QWidget(parent) {
    UI();
    
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
    QUrl url;
    for(int i = 0; i < argc; i ++) {
        url.setPath(QString::fromLatin1(argv[i]));
        if(url.isValid()) {
            /* add to playlist */
            playlist->addMedia(QUrl::fromLocalFile(QString::fromLatin1(argv[i])));
            
        }
    }
    // autoplay
    player->play();
    return true;
}

void Window::setPlayer(Player *player) {
    this->player = player->getPlayer();
    this->playlist = player->getPlaylist();
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
    taglistWidget = new QWidget(this);
    tabWidget = new QWidget(this);
    menuWidget = new QWidget(this);
    
    //widgets
    vLLayout->addWidget(videoWidget);
    vLLayout->addWidget(toolWidget);
    vRLayout->addWidget(tabWidget);
    vRLayout->addWidget(taglistWidget);
    vRLayout->addWidget(menuWidget);
    
    //toolwidget
    QHBoxLayout *RTLayout = new QHBoxLayout;
    toolWidget->setLayout(RTLayout);
    previous = new QToolButton;
    next = new QToolButton;
    play = new QToolButton;
    RTLayout->addSpacing(10);
    RTLayout->addWidget(previous);
    RTLayout->addWidget(play);
    RTLayout->addWidget(next);
    
    
    
    
}
