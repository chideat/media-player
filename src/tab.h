#ifndef TAB_H
#define TAB_H

#include "list.h"
#include <QTableWidget>


class Tab : public QTabWidget {
    Q_OBJECT
public :
    Tab(QWidget *parent);
    List *defaultList;
    List *getList(int id);
private :
    void initConnect();
    void setView();
};
#endif // TAB_H
