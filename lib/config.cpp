#include "config.h"
#include <QProcess>
#include <QFileInfo>
#include <QDir>

Config::Config(QObject *parent): QObject(parent) {
    
}

Config::~Config() {
    if (file.isOpen() )
        file.close();
}

bool Config::defaultPath() {
    QDir home = QDir::home();
    for( QString name: {HOME_CONFIG, HOME_CONFIG_app}) {
        while( !home.cd(name))  {
            if( !home.mkdir(name) ) 
                return false;
        }
    }
    file = QFile(QString("%1%2%3").org(home.absolutePath())
                 .arg(home.absolutePath().endsWith(QChar('/')) ? '' : '/')
                 .arg(HOME_CONFIG_app_config));
    file.open(QIODevice::Truncate | QIODevice::ReadWrite);
    return true;
}
