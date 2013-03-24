#include <QWidget>
#include <QApplication>
#include "player.h"
#include "window.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window *window = new Window();
    window->setAttribute (Qt::WA_ShowModal,true);
    //window->setWindowOpacity (1);
   // window->setWindowFlags (Qt::FramelessWindowHint);
    window->setAttribute (Qt::WA_TranslucentBackground);
    window->show();
    return app.exec();
}
