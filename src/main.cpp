#include <QWidget>
#include <QApplication>
#include "player.h"
#include "window.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
     Window *window = new Window();
     
     //load in threads
     
     // in steps
     window->show();

    return app.exec();
}
