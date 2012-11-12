LIBS += -L/usr/lib/ -ltag
INCLUDEPATH += /usr/include/taglib/


QT += phonon
OBJECTS_DIR = ./object
MOC_DIR = ./moc
TEMPLATE = app
TARGET = ./bin/GMusic
DEPENDPATH += . src src/img
INCLUDEPATH += . src

SOURCES += \
    src/main.cpp \
    src/player.cpp \
    src/window.cpp \
    src/load.cpp \
    src/list.cpp \
    src/tab.cpp \
    src/up.cpp \
    src/down.cpp \
    src/queue.cpp

HEADERS += \
    src/player.h \
    src/window.h \
    src/load.h \
    src/list.h \
    src/tab.h \
    src/up.h \
    src/down.h \
    src/types.h \
    src/queue.h

RESOURCES += src/img/icons.qrc

OTHER_FILES += \
    概要.txt



