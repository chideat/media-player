#include "window.h"
#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

#include <fileref.h>
#include <mpegfile.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <id3v2tag.h>
#include <apetag.h>

#include <QFileInfo>
#include <QDebug>
#include <QTime>
#include <QSettings>
#include <QCloseEvent>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#define STORAGE "/home/thinking/.config/media/playlist.db"

using namespace TagLib;

//typedef Window Operator;

Window::Window(QWebView *parent):QWebView(parent) {
    hide();
    //setFixedSize(800, 510);
    setWindowTitle(tr("media-player"));
    setWindowIcon(QIcon(":/img/media.png"));
    this->setContextMenuPolicy(Qt::NoContextMenu);
    //webkit attribute set
    player = new Player;
    position = -1;
    
    page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    
    connect(page()->mainFrame(), &QWebFrame::javaScriptWindowObjectCleared, [=](){
        page()->mainFrame()->addToJavaScriptWindowObject(QString("Operator"), this);
        page()->mainFrame()->addToJavaScriptWindowObject(QString("Player"), player->getPlayer());
    });
    connect(this, &Window::started, this, &Window::run);
    connect(player->getPlaylist(), &QMediaPlaylist::currentIndexChanged, [=](int index) {
        QPixmap tmp;
        QFileInfo info(player->getPlaylist()->media(index).canonicalUrl().toLocalFile());
        MPEG::File file(info.absoluteFilePath().toUtf8());
        ID3v2::FrameList  pics = file.ID3v2Tag()->frameListMap()["APIC"];
        if(!pics.isEmpty()) {
            ID3v2::AttachedPictureFrame *attached = static_cast<ID3v2::AttachedPictureFrame *>(pics.front());
            tmp.loadFromData((const unsigned char *)attached->picture().data(), attached->picture().size(), "JPEG");
        }
        else {
            tmp.load(":/img/default.png");
        }
        tmp = tmp.scaled(96, 96, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setPic(tmp);
        emit updateMetaData(index);
    });
    connect(player->getPlayer(), &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
        switch(state) {
        case QMediaPlayer::PlayingState:
            emit stateChanged(1);
            break;
        case QMediaPlayer::PausedState:
        case QMediaPlayer::StoppedState:
            emit stateChanged(0);
            break;
        }
    });
    connect(this, &Window::loadFinished, [=]() {
        QFile file(STORAGE);
        if(file.exists()) {
            file.open(QIODevice::ReadOnly);
            QXmlStreamReader stream(&file);
            int index = player->getPlaylist()->mediaCount();
            while(!stream.atEnd() && !stream.hasError()) {
                QXmlStreamReader::TokenType token = stream.readNext();
                if(token == QXmlStreamReader::StartDocument) 
                    continue;
                if(token == QXmlStreamReader::StartElement) {
                    if(stream.name() == "medias") 
                        continue;
                    if(stream.name() == "media") {
                        QXmlStreamAttributes attrs = stream.attributes();
                        stream.readNext();
                        if(stream.tokenType() == QXmlStreamReader::Characters) {
                            run("#mediaList", QStringList(stream.text().toString().remove(0, 7)), index ++);
                            if(attrs.hasAttribute("actived")) {
                                player->getPlaylist()->setCurrentIndex(index - 1);
                                player->getPlayer()->pause();
                                player->getPlayer()->setPosition(attrs.value("duration").toString().toLongLong());
                                player->play(-1);
                            }
                        }
                    }
                }
            }
        }
    });
    load(QUrl("qrc:/index.html"));
    show();
}

bool Window::setMetaData(QString &meta, QWebElement element) {
    
}

//bool Window::setPic(QPixmap *pixmap) {

//}

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
    if(id < 0 && position >= 0) {
        player->getPlayer()->setPosition(position);
        position = -1;
    }
}

void Window::previous() {
    player->getPlaylist()->previous();
    //default to play
    player->getPlayer()->play();
}

void Window::next() {
    player->getPlaylist()->next();
    //default to play
    player->getPlayer()->play();
}

void Window::setMode(int mode) {
    player->getPlaylist()->setPlaybackMode((QMediaPlaylist::PlaybackMode)mode);
}

void Window::setPosition(int x, int width) {
    position = player->getPlayer()->duration() * ((x * 1.0) / width);
    if(player->getPlayer()->state() == QMediaPlayer::PlayingState) {
        player->getPlayer()->setPosition(position);
        position = -1;
    }
}

void Window::setVolume(double per) {
    player->getPlayer()->setVolume(int(MAX_VOLUME * per));
}

void Window::setMuted(bool flag) {
        player->getPlayer()->setMuted(flag);
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
            element.appendInside(tr("<div class='%1 mediaRow''  id='%2'><div class='c0'>%3</div><div class='c1'>%4</div><div class='c2' duration='%5'>%6</div></div>")
                                 .arg(count % 2 == 0 ? "even" : "odd")
                                 .arg(count ++)
                                 .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)))
                                 .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true)))
                                 .arg(length)
                                 .arg(QTime(0, length/60, length%60).toString("mm:ss")));
        }
    }
}

void Window::setPic(QPixmap pix) {
    pixmap = pix;
}

QPixmap Window::getPic() const {
    return pixmap;
}

void Window::closeEvent(QCloseEvent *event) {
     //   QSettings store(QSettings::IniFormat, QSettings::UserScope, tr("media"), tr("media-player"));
    //    store.beginGroup("recent");
    //    store.setValue("media", "test1");
    //    store.setValue("media", "test2");
    //    store.setValue("media", "test3");
    //    store.endGroup();
    //here store the playlist
    
    int count = player->getPlaylist()->mediaCount();
    int current = player->getPlaylist()->currentIndex();
    if(count > 0) {
        QFile file(STORAGE);
        file.open(QIODevice::Truncate | QIODevice::WriteOnly);
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        
        stream.writeStartElement("medias");
        stream.writeAttribute("date", QDate::currentDate().toString("yyyy-MM-dd"));
        for(int i = 0; i < count;i ++) {
            if(i == current) {
                stream.writeStartElement("media");
                stream.writeAttribute("actived", "actived");
                stream.writeAttribute("duration", tr("%1").arg(player->getPlayer()->duration()));
                stream.writeCharacters(player->getPlaylist()->media(i).canonicalUrl().toString());
                stream.writeEndElement();
            }
            else 
                stream.writeTextElement("media", player->getPlaylist()->media(i).canonicalUrl().toString());
        }
        stream.writeEndElement(); // bookmark
        stream.writeEndDocument();
        file.close();
    }
    
    event->accept();
}

Window::~Window() {}
