#include "window.h"
#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <fileref.h>
#include <mpegfile.h>
#include <QFileInfo>
#include <QDebug>
#include <QTime>

typedef Window Operator;

Window::Window(QWebView *parent):QWebView(parent) {
    setWindowTitle(tr("media-player"));
    this->setContextMenuPolicy(Qt::NoContextMenu);
    //webkit attribute set
    player = new Player;
    
    page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    
    connect(page()->mainFrame(), &QWebFrame::javaScriptWindowObjectCleared, [=](){
        page()->mainFrame()->addToJavaScriptWindowObject(QString("Operator"), this);
    });
    connect(this, &Window::started, this, &Window::run);
    connect(player->getPlaylist(), &QMediaPlaylist::currentIndexChanged, [=](int index) {
        page()->mainFrame()->evaluateJavaScript(tr("updateMetaData(%1)").arg(index));
    });
    connect(player->getPlayer(), &QMediaPlayer::positionChanged, [=](qint64 position){
        if(player->getPlayer()->duration() >= 0)
            page()->mainFrame()->evaluateJavaScript(tr("updatePosition(%1)").arg(100.0 * position / player->getPlayer()->duration()));
    });
    
    //load html
    load(QUrl("qrc:/index.html"));
}

bool Window::setMetaData(QString &meta, QWebElement element) {
    
}

bool Window::setPic(QPixmap *pixmap) {
    
}

bool Window::setLyric(QString &lyric) {
    
}

void Window::addMedia(int count) {
    QStringList fileNames = QFileDialog::getOpenFileNames (NULL, tr("Select Media..."), 
                                                           QStandardPaths::displayName(QStandardPaths::MusicLocation), tr("Music Files (*.mp3);;All Files (*.*)"));
    emit started("#mediaList", fileNames, count);
}

void Window::addMedias() {
    
}

void Window::rmMedia(int id) {
    
}

void Window::clean() {
    
}

void Window::playOpause(int id) {
        player->play(id);
}

void Window::previous() {
    player->getPlaylist()->previous();
}

void Window::next() {
    player->getPlaylist()->next();
}

void Window::setMode(int mode) {
    player->getPlaylist()->setPlaybackMode((QMediaPlaylist::PlaybackMode)mode);
}

void Window::setPosition(int x, int width) {
    player->getPlayer()->setPosition(player->getPlayer()->duration() * ((x * 1.0) / width));
}

void Window::setVolume(double per) {
    player->getPlayer()->setVolume(MAX_VOLUME * per);
}

void Window::setVolume(int x, int width) {
    //qDebug()<<(60 * x)/ width;
    player->getPlayer()->setVolume((MAX_VOLUME * x)/ width);
}

void Window::setMuted(int mute) {
    if(mute == 0)
        player->getPlayer()->setMuted(false);
    else 
        player->getPlayer()->setMuted(true);
}

QWebElement Window::getElement(QString label) {
    return page()->mainFrame()->documentElement().findFirst(label);
}

void Window::run(QString label, QStringList medias, int c) {
    QWebElement element = getElement(label);
    int count = c, length = 0;
    if(element.isNull() || medias.isEmpty())
        return ;
    //here get the count of medias
    if(count < 0)
        count = 0;
    //i add the elements one by one 
    foreach (QString m, medias) {
        if(m.isEmpty()) continue;
        QFileInfo fileInfo(m);
        TagLib::FileRef file(fileInfo.absoluteFilePath().toUtf8());
        if(!file.isNull() && player->getPlaylist()->addMedia(QUrl::fromLocalFile(m))) {
            length = file.audioProperties()->length();
            element.appendInside(tr("<div class='%1 mediaRow''  id='%2'><div class='c0'>%3</div><div class='c1'>%4</div><div class='c2' length='%5'>%6</div></div>")
                                 .arg(count % 2 == 0 ? "even" : "odd")
                                 .arg(count ++)
                                 .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)))
                                 .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true)))
                                 .arg(length)
                                 .arg(QTime(0, length/60, length%60).toString("mm:ss")));
        }
    }
}
