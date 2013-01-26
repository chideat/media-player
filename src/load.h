#ifndef LOAD_H
#define LOAD_H

#include <QThread>

class QWebElement;
class QStringList;
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
    bool load(QStringList &media, QWebElement element);
protected:
    void run();
};

#endif // LOAD_H
