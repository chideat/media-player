#ifndef LIST_H
#define LIST_H

#include "load.h"
#include <QWidget>
#include <QTableWidget>
#include <QFileInfo>

class List :public QTableWidget {
    Q_OBJECT
public :
    List(QWidget *parent);
    QList<qint32> *list;
private :
    Load *load;

    void setView();
    void initConnect();
    QString getPath(qint32 id);
    qint32 getRandom();
    void scrollToRow();
public slots:
    bool remove(qint32);
    //void setLoad(LoadType type, QString path);
    void rowClicked(int r, int);
    bool addItem(char *argv);
signals :
    void next(QString path);
    void jump(QString path);
};
#endif // LIST_H
