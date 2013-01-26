#ifndef LOAD_H
#define LOAD_H

#include <QThread>
#include <QWebElement>
#include <QStringList>

/**
 * @brief The load class
 * this class used to load medias from local or network
 * as 
 * add local media
 * add local medias
 * add network media
 */
class Load:  QThread{
    Q_OBJECT
public:
    Load(QThread *parent = NULL);
    void setElement(QWebElement element);
    void setMedias(QStringList &medias);
protected:
    void run();
    
    QWebElement element;
    QStringList *medias;
};

#endif // LOAD_H
