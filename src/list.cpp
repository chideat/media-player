#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableView>
#include <QScrollBar>
#include <QTime>
#include <QDebug>

List::List(QWidget *parent) : QTableWidget(0, 5, parent) {
    list = new QList<qint32>;
    history = new History;
    mutex = new QMutex;
    model = DEFAULT;
    currentID = -1;

    //srandom
    srandom((unsigned)time(NULL));
    setView();
}
void List::setView(){
    //init table
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    resizeRowsToContents();
    setContentsMargins(0,0,0,0);
    setColumnHidden(0,true);
    setColumnWidth(1,190);
    setColumnWidth(2,85);
    setColumnWidth(3,60);
    setColumnHidden(4,true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setShowGrid(false);
    setAlternatingRowColors(true);
    setAutoScroll(true);
    setAutoScrollMargin(0);
    setWordWrap(false);
//    setHorizontalScrollBar(Qt::ScrollBarAlwaysOff);
//    horizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border:0px solid grey;width:4px;background:#888888;}");
    setStyleSheet("QTableView:Item{selection-background-color: #DADADA}");
        //行背景色

    initConnect();
}

void List::initConnect() {
    connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(rowClicked(int,int)));
}

QString List::getPath(qint32 id) {
    if(id < 0 || id >= rowCount ())
        return NULL;
    QTableWidgetItem  *item1 = this->item(id,4);
    scrollToItem (item1);
    return item1->text();
}

qint32 List::getRandom() {
    qreal percentage = (random() % 50 + 2) / 100.0;//=<0.5
    return (int)(list->indexOf(currentID) + list->size() * percentage) % list->size() + 1;
}


//void List::aboutToFinish() {
//    if(history->hasNext()) {
//        nextID = history->getNext();
//    }
//    else {
//        switch(model) {
//            case SINGAL :
//                //do nothing
//                break;
//            case DEFAULT :
//                nextID = list->indexOf(currentID) + 1;
//                break;
//            case REPEAT_SINGAL :
//                nextID = currentID;
//                break;
//            case REPEAT_ALL :
//                nextID = list->at((list->indexOf(currentID) + 1) % list->size());
//                break;
//            case SHUFFLE :
//                nextID = list->at(getRandom());
//                break;
//        }
//    }
//}

void List::previous() {
    if(history->hasPrevious()) {
        currentID = history->previous();
        emit jump(getPath(list->indexOf(currentID)));
        scrollToRow();
    }
    else {
        //do nothing
    }
}

void List::next() {
    if(list->size() > 0) {
        if(history->hasNext()) {
            currentID = history->getNext();
            emit jump(getPath(list->indexOf(currentID)));
        }
        else {
            switch(model) {
                case SINGAL :
                case DEFAULT: {
                        qint32 id = list->indexOf(currentID) + 1;
                        if(id < list->size()) {
                            currentID = list->at(id);
                            emit jump(getPath(id));
                        }
                        break;
                }
                case REPEAT_SINGAL :
                    if(list->contains(currentID)) {
                        emit jump(getPath(list->indexOf(currentID)));
                    }
                    break;
                case REPEAT_ALL :{
                    qint32 id = (list->indexOf(currentID) + 1) % list->size();
                    currentID = list->at(id);
                    emit jump(getPath(id));
                    break;
                }
                case SHUFFLE : {
                    qint32 id = getRandom();
                    currentID = list->at(id);
                    emit jump(getPath(id));
                    break;
                }
            }
            history->enqueue(currentID);
        }
        scrollToRow();
    }
}

void List::rowClicked(int r, int /*c*/) {
    if(r < 0 || r > list->size())
        return ;
    history->init();
    currentID = list->at(r);
    emit jump(getPath(r));
    history->enqueue(currentID);
}

void List::scrollToRow() {
    setCurrentCell (list->indexOf(currentID),1);
    scrollToItem (itemAt (list->indexOf(currentID),1));
}

void List::modelChanged(Model model) {
    this->model = model;
}

bool List::remove(qint32 id) {
    if(id < 0 || id >= rowCount())
        return false;
    removeRow(id);
    list->removeAt(id);
    return true;
}

bool List::addItem(Music *item) {
    if(item == NULL)
        return false;
    mutex->lock();
    QTableWidgetItem *idItem = new QTableWidgetItem(QVariant(item->id).toString ());
    QTableWidgetItem *nameItem = new QTableWidgetItem(item->name);
    nameItem->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
    QTableWidgetItem *artistItem = new QTableWidgetItem(item->artist);
    artistItem->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
    QTime timeLong(0,item->time/60,item->time%60);
    QTableWidgetItem *timeItem = new QTableWidgetItem(timeLong.toString ("mm:ss"));
    timeItem->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
    QTableWidgetItem *pathItem = new QTableWidgetItem(item->path);
    pathItem->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);

    int rowCount = this->rowCount ();
    list->append(item->id);
    this->insertRow (rowCount);
    this->setItem (rowCount, 0,idItem);
    this->setItem (rowCount, 1, nameItem);
    this->setItem (rowCount, 2, artistItem);
    this->setItem (rowCount, 3, timeItem);
    this->setItem (rowCount, 4, pathItem);
    delete item;
    mutex->unlock();
    
    return TRUE;
}

void List::deleteWhat(qint8 kind) {
    switch(kind) {
    case -1:{
        //clear the list
        mutex->lock();
        while(rowCount() > 0){
            removeRow(rowCount() - 1);
            list->removeLast();
        }
        currentID = -1;
        history->clear();
        history->init();
        mutex->unlock();
        break;
    }
    case 0: {
        //delete current
        break;
    }
    case 1:{
        //delete current selected
        list->removeAt(currentRow());
        this->removeRow(currentRow());
    }
    }
}
