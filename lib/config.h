#ifndef SETTING_H
#define SETTING_H

#include <QString>
#include <QFile>
#include <QVariant>
#include <QList>
#include <QMap>
#include <QVariant>

#define HOME_CONFIG ".config"
#define HOME_CONFIG_app "media-player"
#define HOME_CONFIG_app_config "mp.conf"
class Config: public QObject {
    Q_OBJECT
    Q_ENUMS(Mode)
public:
    enum Mode { O_NONE, O_RD, O_WR };
    
    Config(QObject *parent = NULL);

    QFile file;
    QMap<QString, QVariant> *config;
    
    void operator <<(QString key, QVariant value);
public Q_SLOTS:
    bool constains(QString key);
    void set(QString key, QVariant value);
    QVariant get(QString key);
    void importConfig(QMap<QString, QVariant> items);
    QMap<QString, QVariant> exportConfig();
    
    bool clean();
    bool rmConfigFile();
protected:
    bool defaultPath();
    void writer();
    void reader();
    
};

#endif // SETTING_H
