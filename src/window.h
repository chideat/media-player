#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QWebView>
#include <QWebFrame>
#include <QWebElement>
#include <QPixmap>

class Window : public QWebView {
    Q_OBJECT
public: 
    Window(QWebView *parent = NULL);
    
public slots:
//    bool setMetaData(int *meta, QWebElement element);
//    bool setPic(QPixmap *pixmap);
//    bool setLyric(QString &lyric);
    
//    //call by javascript
//    void addMedia();
//    void addMedias();
//    void setMode(int mode);
//    void rmMedia(int id);
//    void clean();
//    void playOpause(int flag);
//    void previous();
//    void next();
};
#endif // WINDOW_H
