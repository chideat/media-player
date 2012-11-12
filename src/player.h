/*
    the player class deals with the independenth of the player
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QString>
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>


/*
    here this thread is just used to load the source
*/
 /*:public QThread*/
#include <QObject>
#include <QQueue>

class Player : public QObject{
    Q_OBJECT
public :
    Player(QWidget *parent=NULL);
    Phonon::SeekSlider *getSeekSlider();
    Phonon::VolumeSlider *getVolumeSlider();
    Phonon::State getState();
private :
    QWidget *parent;
    Phonon::SeekSlider *seekSlider;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

public slots:
    void setTickInterval(qint64 interval=900);
    void setVolume(double volume=0.3);
    void setName(QString);

    bool play(QString path);
    bool pause();
    //emit
    void eTick(qint64);
    void eFinished();
    void eStateChanged(Phonon::State newstate, Phonon::State oldstate);
signals:
    void finished(QString path);
    void tick(qint64 );
    void stateChanged(Phonon::State newstate);

};
#endif // PLAYER_H