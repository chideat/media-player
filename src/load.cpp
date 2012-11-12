#include "load.h"
#include <QFileDialog>
#include <QDebug>

#include <tag.h>
#include <fileref.h>
#include <mpegheader.h>
#include <mpegfile.h>
#include <stdlib.h>

using namespace TagLib;

Load::Load(QWidget *parent) :QThread(parent) {
    numOfMusic = 0;
    supportedMedia << "mp3"<<"wma"<<"ogg"<<"mp4";
    connect (parent,SIGNAL(destroyed()),this,SLOT(quit()));
}

void Load::run () {
    switch(loadType) {
    case LOAD_DIR : {
        loadDir (path,0);
        break;
    }
    case LOAD_FILE :{
        loadFile (path);
        break;
    }
    case LOAD_FILES : {
       // loadFiles (files);
        break;
    }
    }
   // emit loadFinished (true);
    qDebug()<<"load finished";
    this->quit();
}

void Load::loadDir (QString &path, int deepth) {
    //deepth is used to take the case of circle include
    if(deepth > 5)
        return ;
    if(path.isNull () || path.isEmpty () )
        return ;
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList (QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    loadFiles (fileInfos);

    QFileInfoList dirList = dir.entryInfoList (QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable);
    foreach(QFileInfo dirPath,dirList) {
        QString tmp = dirPath.absoluteFilePath ();
        loadDir (tmp,deepth + 1);
    }
}

void Load::loadFile (QFileInfo fileInfo) {
    if(supportedMedia.contains (fileInfo.suffix ())) {
        FileRef file(fileInfo.absoluteFilePath().toUtf8());
        if(!file.isNull()) {
            if(file.tag() == NULL || file.audioProperties() == NULL)
                return ;
            Music *item = new Music;
            item->id = numOfMusic ++;
            item->artist = file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true));
            item->name = file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true));
            item->path = fileInfo.absoluteFilePath ();
            item->time = file.audioProperties()->length();
            emit newItem (item);
        }
    }
}


void Load::loadFiles (QFileInfoList fileInfos) {
    //the
    if(fileInfos.isEmpty ())
        return ;
    foreach(QFileInfo fileInfo, fileInfos) {
        qDebug()<<fileInfo.baseName();
        loadFile(fileInfo);
    }
}

void Load::loadFiles(QStringList files) {
    if(files.isEmpty())
        return ;
    foreach(QString file,files) {
        QFileInfo fileInfo(file);
        loadFile(fileInfo);
        msleep(30);
    }
}

void Load::setPath (QString &path) {
    this->path = path;
}

void Load::setLoadType (LoadType type) {
    loadType = type;
}

