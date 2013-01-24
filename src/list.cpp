#include "list.h"
#include <QFile>
#include <QFileInfo>
#include <QWebView>
#include <QWebFrame>
#include <tag.h>
#include <fileref.h>
#include <mpegheader.h>
#include <mpegfile.h>
#include <QDebug>

List::List(QWidget *parent) : QWidget(parent) {
    view = new QWebView(this);
    view->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    view->setFixedWidth(270);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //load html

    
    frame = view->page()->mainFrame();
    connect(frame, &QWebFrame::javaScriptWindowObjectCleared, [=](){
        frame->addToJavaScriptWindowObject(QString("List"), this);
    });
//    QFile file(":/list.html");
//    file.open(QIODevice::ReadOnly);
//    view->setHtml(file.readAll());
//    file.close();
    view->load(QUrl("qrc:/list.html"));
}

bool List::addItem(char *argv, int playList) {
    if(argv == NULL) return false;
    QFileInfo fileInfo(QString::fromUtf8(argv));
    TagLib::FileRef file(fileInfo.absoluteFilePath().toUtf8());
    if(!file.isNull()) {
        if(file.tag() == NULL || file.audioProperties() == NULL)
            return false;
        frame->evaluateJavaScript(tr("addMedia(\"<tr class='row' id='10'><td class='media'>%2</td><td class='arctist'>%1</td></tr>\")")
                                  .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true)))
                                  .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true))));
    }
    return true;
}

void List::play(const QString &id) {
    qDebug()<<"asdfasdf";
}
