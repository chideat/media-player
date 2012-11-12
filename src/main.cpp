#include <QApplication>
#include <QtGui>
#include "window.h"



int main(int argc, char **argv) {
    qRegisterMetaType<Music>("Music &");

    QApplication app(argc, argv);

    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

    app.setApplicationName("GMusic");
    app.setQuitOnLastWindowClosed(true);
    app.setApplicationVersion ("1.0");

    Window window;
    window.setWindowTitle ("GMuisc");
    window.move(510,40);

    window.show ();

    return app.exec();
}
