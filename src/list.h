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
private :
    void setView();
public slots:
    bool addItem(char *argv);
};
#endif // LIST_H
