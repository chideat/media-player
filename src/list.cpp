#include "list.h"
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableView>
#include <QScrollBar>

#include <fileref.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <apetag.h>

List::List(QWidget *parent) : QTableWidget(0, 2, parent) {
    setView();
}
void List::setView(){
    //init table
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    resizeRowsToContents();
    setContentsMargins(0,0,0,0);
    setColumnWidth(0,180);
    setColumnWidth(1,65);
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
}


bool List::addItem(char *argv) {
    QFileInfo fileInfo(argv);
    TagLib::FileRef file(fileInfo.absoluteFilePath().toUtf8());
    //QPixmap pix;
    if(!file.isNull()) {
        if(file.tag() == NULL || file.audioProperties() == NULL)
            return false;
        QTableWidgetItem *song = new QTableWidgetItem(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)));
        song->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QTableWidgetItem *singer = new QTableWidgetItem(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true)));
        singer->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        /* add to playlist */ 
        int rowCount = this->rowCount(); 
        insertRow (rowCount);
        setItem (rowCount, 0, song);
        setItem (rowCount, 1, singer);
    }
    return true;
}