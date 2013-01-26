QMAKE_CXXFLAGS += -std=c++0x

QT += multimedia  widgets webkitwidgets

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
    src/window.cpp

HEADERS += \ 
    src/player.h \
    src/load.h \
    src/window.h

RESOURCES += \
    src/xml/html.qrc

OTHER_FILES += \
    doc/log.txt