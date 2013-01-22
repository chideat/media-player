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
//    QWidget *widget = new QWidget;
//    QToolButton *button = new QToolButton;
//    button->setIcon(QIcon(":/16x16/play.png"));
//    QHBoxLayout *layout = new QHBoxLayout;
//    widget->setLayout(layout);
//    layout->addWidget(button);
//    button->setStyleSheet("QToolButton{border:0px;}");
//    button->setCheckable(true);
//    button->setChecked(true);
//    widget->show();
    return app.exec();
}
