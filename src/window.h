#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QWebView>
#include <QWebFrame>
#include <QWebElement>
#include <QHash>

class Window : public QWebView {
    Q_OBJECT
public: 
    Window(QWebView *parent = NULL);
    
public slots:
    bool setMetaData(QString &meta, QWebElement element);
    bool setPic(QPixmap *pixmap);
    bool setLyric(QString &lyric);
    
    //call by javascript
    void addMedia();
    void addMedias();
    void rmMedia(int id);
    void clean();
    void playOpause(int flag);
    void previous();
    void next();
    void setMode(int mode);
};
#endif // WINDOW_H
