LIBS += -L/usr/lib/ -ltag
INCLUDEPATH += /usr/include/taglib/


QT += multimedia widgets
QMAKE_CXXFLAGS += -std=c++0x

OBJECTS_DIR = ./object
MOC_DIR = ./moc
TEMPLATE = app
DESTDIR_TARGET = ./bin/media-player
DEPENDPATH += . src src/img
INCLUDEPATH += . src

SOURCES += \
    src/main.cpp \
    src/player.cpp \
    src/load.cpp \
    src/playlist.cpp \
    src/window.cpp

HEADERS += \ 
    src/player.h \
    src/load.h \
    src/playlist.h \
    src/window.h

RESOURCES += src/img/icons.qrc

OTHER_FILES +=