#include "window.h"
#include <QWebElement>
#include <QDebug>
#include <QFileDialog>

typedef Window Operator;
Window::Window(QWebView *parent):QWebView(parent) {
    setWindowTitle(tr("media-player"));

    //webkit attribute set
    page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

    connect(page()->mainFrame(), &QWebFrame::javaScriptWindowObjectCleared, [=](){
        page()->mainFrame()->addToJavaScriptWindowObject(QString("Operator"), this);
    });

    //load html
    load(QUrl("qrc:/index.html"));
}

bool Window::setMetaData(QString &meta, QWebElement element) {
    
}

bool Window::setPic(QPixmap *pixmap) {
    
}

bool Window::setLyric(QString &lyric) {
    
}

void Window::addMedia() {
    QFileDialog::s
}

void Window::addMedias() {
    
}

void Window::rmMedia(int id) {
    
}

void Window::clean() {
    
}

void Window::playOpause(int flag) {
    
}

void Window::previous() {
    
}

void Window::next() {
    
}

void Window::setMode(int mode) {
    
}
