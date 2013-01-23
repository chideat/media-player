#ifndef LIST_H
#define LIST_H

#include <QWidget>
class QWebView;
class QWebFrame;

class List : public QWidget {
    Q_OBJECT
public :
    List(QWidget *parent = NULL);
private :
    QWebView *view;
    QWebFrame *frame;
public slots:
    bool addItem(char *argv, int playList = 0);
    void play(const QString &id);
};
#endif // LIST_H
