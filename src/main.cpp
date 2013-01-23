#include "player.h"
#include "load.h"
#include "window.h"

#include <QWidget>
#include <QApplication>

int main(int argc, char **argv) {
    QTextCodec::codecForName("UTF-8");
    
    QApplication app(argc, argv);
     Window *window = new Window(new Player);
     // in steps
     char **playlist = (argc > 1 ? argv + 1 : NULL);
     window->initPlaylist(argc - 1, playlist);
     window->show();
     
    return app.exec();
}
