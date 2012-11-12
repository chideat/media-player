#ifndef LOAD_H
#define LOAD_H


#include <QThread>
#include <QHash>
#include <QDir>
#include <QQueue>
#include "types.h"

/*
    this thread is created to load the music files from the harddisk
    it communicate with class music_list and it's parent
    in fact, it just want to send the datas to musicList and the playing list

    here l used slot to send the message maybe it's not effection enough
*/

class Load : public QThread {
    Q_OBJECT
public :
    Load(QWidget *parent = NULL);
    void setLoadType(LoadType type);
    void setPath(QString &path);
private :
    QString path;
    QString files;
    LoadType loadType;
    QStringList supportedMedia;
    qint32 numOfMusic;
protected :
    void run();
public slots:
    void loadDir(QString &path,int deepth = 0);
    void loadFile (QFileInfo fileInfo);
    void loadFiles (QFileInfoList fileInfos);
    void loadFiles (QStringList files);
signals:
    // i doubted that whether it needs this signal
    //before add to the table, it's necessary to anaylise the music files
    void newItem(Music *item);
    void loadFinished(bool flag);
};
#endif // LOAD_H
