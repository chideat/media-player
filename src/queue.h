#ifndef QUEUE_H
#define QUEUE_H

#include <QStack>
#include <QQueue>

/*
    here stores the history with id
*/
class History{
public :
    History();
    qint32 size();
    void enqueue(qint32 id);
    //when the history pop,the id set to -1
    qint32 dequeue();
    qint32 previous();
    void clear();
    //id ge than 0
    bool contains(qint32 id);
    bool remove(qint32 id);
    bool hasNext();
    bool hasPrevious();
    qint32 getNext();
    void init();
private :
    QQueue<qint32> *history;
    qint32 currentIndex;
};


#endif // QUEUE_H
