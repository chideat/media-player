#ifndef TYPES_H
#define TYPES_H
#include <QString>

enum LoadType {
    LOAD_DIR,
    LOAD_FILE,
    LOAD_FILES
};

enum Model {
    SINGAL,
    REPEAT_SINGAL,
    DEFAULT,
    REPEAT_ALL,
    SHUFFLE
} ;


class Music{
public :
    Music(){
        id = 0,
        name = "";
        path = "";
        artist = "";
        time = 0;
    }
    qint32 id;
    QString name;
    QString path;
    QString artist;
    qint64 time;
};

#endif // TYPES_H
