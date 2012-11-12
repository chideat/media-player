#ifndef LIST_H
#define LIST_H

#include "types.h"
#include "queue.h"
#include "load.h"
#include <QWidget>
#include <QTableWidget>
#include <QFileInfo>
#include <QMutex>

class List :public QTableWidget {
    Q_OBJECT
public :
    List(QWidget *parent);
    QList<qint32> *list;
private :
    QMutex *mutex;
    Load *load;
    History *history;
    Model model;
    qint32 currentID;

    void setView();
    void initConnect();
    QString getPath(qint32 id);
    qint32 getRandom();
    void scrollToRow();
public slots:
    //player
//    void aboutToFinish();
   // void eFinished();
    void next();
    void previous();
    void modelChanged(Model model);
    bool remove(qint32);
    //void setLoad(LoadType type, QString path);
    void rowClicked(int r, int);
    bool addItem(Music *item);
    void deleteWhat(qint8 kind);/* -1 -- all , 0 -- current, 1 -- current selected  */
signals :
    void next(QString path);
    void jump(QString path);
};
#endif // LIST_H
