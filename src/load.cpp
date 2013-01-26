//#include "load.h"
//#include <fileref.h>
//#include <mpegfile.h>
//#include <QFileInfo>
//#include <QDebug>
//using namespace TagLib;


//Load::Load(QThread *parent) : QThread(parent) {
//    connect(this, &Load::finished, this, &Load::deleteLater);
//}

//void Load::run() {
//    if(element.isNull() || medias.isEmpty())
//        this->quit();
//    //here get the count of medias
//    if(count < 0)
//        count = 0;
//    foreach (QString m, medias) {
//        if(m.isEmpty()) continue;
//        QFileInfo fileInfo(m);
//        FileRef file(fileInfo.absoluteFilePath().toUtf8());
//        if(!file.isNull()) {
//            qDebug()<<element.toOuterXml();
//            element.appendInside(tr("<div>111111</div>"));
//            break;
//            //<div class='odd mediaRow''  id='1'><div class='c0'>asdfasd</div><div class='c1'>asdfasd</div></div>
////                    .arg(count++ % 2 == 0 ? "even" : "odd")
////                    .arg(1)
////                    .arg(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName().trimmed()) : tr(file.tag()->title().toCString(true)))
////                    .arg(file.tag()->artist().isNull() ?  tr("...") : tr(file.tag()->artist().toCString(true))));
//        }
//    }
//     qDebug()<<"finished";
//}

//void Load::setElement(QWebElement element) {
//    this->element = element;
//}

//void Load::setMedias(QStringList medias) {
//    this->medias = medias;
//}

//void Load::setCount(int c) {
//    count = c;
//}
