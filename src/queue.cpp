#include "queue.h"

/*
-1 means no history
and currentIndex means current playing music
*/
History::History() {
    history = new QQueue<qint32>;
    currentIndex = -1;
}


qint32 History::size() {
    return history->size();
}

//keep the size as 30
void History::enqueue(qint32 id) {
    history->enqueue(id);
    currentIndex ++;
    if(history->size() > 30) {
        history->dequeue();
        currentIndex = history->size() - 1;
    }
}


qint32 History::dequeue() {
    return 0;
}


/*
 -1 means no history
*/
qint32 History::previous() {
    if(hasPrevious())
        return history->at(--currentIndex);
    currentIndex = -1;
    return -1;
}


void History::clear() {
    history->clear();
}

bool History::contains(qint32 id) {
    return history->contains(id);
}

bool History::remove(qint32 id) {
    if(history->removeAll(id))
        return true;
    return false;
}

bool History::hasNext() {
    if(history->size() > 0 && currentIndex < history->size() - 1)
        return true;
    return false;
}

bool History::hasPrevious() {
    if(history->size() > 0 && currentIndex > 0)
        return true;
    return false;
}

qint32 History::getNext() {
    if(hasNext())
        return history->at(++currentIndex);
    return history->at(currentIndex);
}

void History::init() {
    currentIndex = history->size() - 1;
}
