#ifndef WINDOW_H
#define WINDOW_H

#include <QWebView>
#include <QWebElement>
#include "player.h"


class Window : public QWebView {
    Q_OBJECT
public: 
    Window(QWebView *parent = NULL);
    ~Window();
    Q_PROPERTY(QPixmap pixmap READ getPic WRITE setPic)
    QPixmap getPic() const;
    void setPic(QPixmap pix);
public slots:
    bool setMetaData(QString &meta, QWebElement element);
//    bool setPic(QPixmap *pixmap);
    bool setLyric(QString &lyric);
    
    //call by javascript
    void addMedia(int count);
    void addMedias();
    void rmMedia(int id);
    void clean();
    void playOpause(int flag);
    void previous();
    void next();
    void setMode(int mode);
    void setPosition(int x, int width);
    void setVolume(double per);
    void setMuted(bool flag);
    void run(QString label, QStringList medias, int c);
protected:
    void closeEvent(QCloseEvent *);
private:
    QWebElement getElement(QString label);
    Player *player;
    qint64 position;
    QPixmap pixmap;
signals:
    void started(QString label, QStringList medias, int c);
    void updateMetaData(int index);
    void stateChanged(int state);
};
#endif // WINDOW_H
