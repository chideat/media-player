QT += multimedia widgets
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/lib/ -ltag
INCLUDEPATH += /usr/include/taglib/

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
    src/window.cpp \
    src/list.cpp

HEADERS += \ 
    src/player.h \
    src/load.h \
    src/playlist.h \
    src/window.h \
    src/list.h

RESOURCES += src/img/icons.qrc

OTHER_FILES += \
    doc/log.txt