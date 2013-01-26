#include "load.h"
#include <fileref.h>
#include <mpegfile.h>
#include <QFileInfo>

using namespace TagLib;

Load::Load(QThread *parent) : QThread(parent) {
    medias  = new QStringList;
    
}

void Load::run() {
    if(element.isNull() || medias == NULL || medias->isEmpty())
        this->quit();
    //here get the count of medias
    int count = 1;
    foreach (QString m, *medias) {
        QFileInfo fileInfo(m);
        FileRef file(fileInfo.absoluteFilePath().toUtf8());
        if(!file.isNull()) {
            element.appendInside(tr("<div class='%1 mediaRow''  id='%2'><div class='c0'>%3</div><div class='c1'>%4</div></div>")
                    .arg(count % 2 == 0 ? "even" : "odd")
                    .arg(count ++)
                    .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)))
                    .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true))));
        }
    }
}

void Load::setElement(QWebElement element) {
    this->element = element;
}

void Load::setMedias(QStringList &medias) {
    this->medias = &medias;
}
