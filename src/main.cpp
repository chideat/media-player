#include "player.h"
#include "load.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QDir>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    QWidget *widget = new QWidget;
    Player *player = new Player(widget, "/home/thinking/Music/1.mp3");

    widget->show();
    return app.exec();
}
