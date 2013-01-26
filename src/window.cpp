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

typedef Window Operator;

Window::Window(QWebView *parent):QWebView(parent) {
    setWindowTitle(tr("media-player"));
    //webkit attribute set
    player = new Player;
    
    page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    
    connect(page()->mainFrame(), &QWebFrame::javaScriptWindowObjectCleared, [=](){
        page()->mainFrame()->addToJavaScriptWindowObject(QString("Operator"), this);
    });
    connect(this, &Window::started, this, &Window::run);
    
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
    
}

void Window::next() {
    
}

void Window::setMode(int mode) {
    
}

QWebElement Window::getElement(QString label) {
    return page()->mainFrame()->documentElement().findFirst(label);
}

void Window::run(QString label, QStringList medias, int c) {
    QWebElement element = getElement(label);
    int count = c;
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
            element.appendInside(tr("<div class='%1 mediaRow''  id='%2'><div class='c0'>%3</div><div class='c1'>%4</div></div>")
                                 .arg(count % 2 == 0 ? "even" : "odd")
                                 .arg(count ++)
                                 .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)))
                                 .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true))));
        }
    }
}
