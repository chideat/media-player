#include "up.h"
#include <QGridLayout>
#include <QSizePolicy>
#include <QSize>
#include <QTime>

#include <fileref.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <apetag.h>


using namespace TagLib;

Up::Up(QWidget *parent) : QWidget(parent) {
    initPlayer();
    initGui();
    initConnect();
}

void Up::initPlayer() {
    player = new Player(this);
    seekSlider = player->getSeekSlider();
    volumeSlider = player->getVolumeSlider();

    player->setName("GMusic");
    player->setTickInterval(/*default*/);
    player->setVolume(0.3);
}

void Up::tick(qint64 tick) {
    QTime displayTime(0,(tick / 60000) % 60, (tick / 1000) % 60);
    time->setText (displayTime.toString ("mm:ss"));
}


void Up::initConnect() {
    //player
    connect(player,SIGNAL(tick(qint64)),this,SLOT(tick(qint64)));
    //connect(player,SIGNAL(aboutToFinish()),this,SLOT(eAboutToFinish()));
    connect(player,SIGNAL(finished(QString)),this,SLOT(eNext()));
    connect(player,SIGNAL(stateChanged(Phonon::State)),this,SLOT(stateChanged(Phonon::State)));
    //action
    connect(buttonPrevious,SIGNAL(released()),this,SLOT(ePrevious()));
    connect(buttonPlayOrPause,SIGNAL(released()),this,SLOT(ePlay()));
    connect(buttonNext,SIGNAL(released()),this,SLOT(eNext()));
}

//gui
void Up::initGui() {
    title = new QLabel(tr("GMusic"));
    title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    title->setMaximumWidth(200);

    time = new QLabel("00:00");
    time->setMaximumWidth(40);

    picture = new QLabel;
    picture->setFrameShape(QFrame::Box);
    picture->setFrameShadow(QFrame::Raised);
    picture->setLineWidth(3);
    picture->setMidLineWidth(2);
    picture->setMaximumHeight(96);
    picture->setMaximumWidth(96);
    QPixmap pixmap(":/default.png");
    pixmap = pixmap.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    picture->setPixmap(pixmap);

    buttonPrevious = new QToolButton;
    buttonPrevious->setIcon (QIcon(":/24x24/previous.png"));
    buttonPrevious->setShortcut (QKeySequence("Ctrl+Up"));
    buttonPrevious->setIconSize (QSize(24,24));
    buttonPlayOrPause = new QToolButton;
    buttonPlayOrPause->setIcon(QIcon(":/24x24/play.png"));
    buttonPlayOrPause->setShortcut (QKeySequence("Ctrl+P"));
    buttonPlayOrPause->setIconSize(QSize(24,24));
    buttonNext = new QToolButton;
    buttonNext->setIcon (QIcon(":/24x24/next.png"));
    buttonNext->setShortcut (QKeySequence("Ctrl+Down"));
    buttonNext->setIconSize (QSize(24,24));

    buttonPlayOrPause->setFocus ();

    //style
    buttonPlayOrPause->setStyleSheet ("QToolButton{border:0px;}");
    buttonPrevious->setStyleSheet ("QToolButton{border:0px;}");
    buttonNext->setStyleSheet ("QToolButton{border:0px;}");

    layout();
}

void Up::layout() {
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    QHBoxLayout *hBoxLayout2 = new QHBoxLayout;
    QGridLayout *grid = new QGridLayout(this);
    QGridLayout *gridLayout = new QGridLayout;

    //slider and time indicate
    hBoxLayout1->setMargin(0);
    hBoxLayout1->setSpacing(0);
    hBoxLayout1->addWidget(seekSlider);
    hBoxLayout1->addSpacing(5);
    hBoxLayout1->addWidget(time);

    //buttons
    hBoxLayout2->setMargin(0);
    hBoxLayout2->setSpacing(0);
    hBoxLayout2->addWidget(buttonPrevious);
    hBoxLayout2->addSpacing(5);
    hBoxLayout2->addWidget(buttonPlayOrPause);
    hBoxLayout2->addSpacing(5);
    hBoxLayout2->addWidget(buttonNext);
    hBoxLayout2->addSpacing(30);
    hBoxLayout2->addWidget(volumeSlider);

    //grid
    gridLayout->setMargin(5);
    gridLayout->setSpacing(0);
    gridLayout->addWidget(title,1,1,1,3,Qt::AlignCenter | Qt::AlignTop);
    gridLayout->addLayout(hBoxLayout1,2,1,1,3,Qt::AlignCenter);
    gridLayout->addLayout(hBoxLayout2,3,1,1,3,Qt::AlignCenter);
    grid->setMargin(5);
    grid->setSpacing(0);
    grid->addWidget(picture,1,1,1,1,Qt::AlignCenter);
    grid->addLayout(gridLayout,1,2,1,1,Qt::AlignCenter);



    //view
    seekSlider->setStyleSheet (
                "QSlider::groove:horizontal {border: 0px solid gray;height:3px;background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);border-image:url(:/handle.png);}"
                           //    "QSlider::handle:horizontal {margin: -20px;}"
                "QSlider::sub-page{background-color:#33EE78;}"
                "QSlider::add-page{background-color:#ADADAD;}"
                );
    volumeSlider->setIconSize(QSize(18,18));
//        volumeSlider->setStyleSheet(
//             //       "QSlider::groove:horizontal {border: 0px solid gray;height:3px;background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
//                    "QSlider::background-color:#33EE78;"
//                    "QSlider::add-page{background-color:#ADADAD;}"
//                    );
}

void Up::update(QString path) {
    if(!path.isNull() && !path.isEmpty()){
        QFileInfo fileInfo(path);
        //here update the picture
        MPEG::File file(fileInfo.absoluteFilePath().toUtf8());
        QPixmap pix;
        if(file.isValid()) {
            this->title->setText(file.tag()->title().isNull() ? tr("%1").arg(fileInfo.baseName()) : tr(file.tag()->title().toCString(true)));
            //get attached picture
            ID3v2::FrameList pictures = file.ID3v2Tag()->frameListMap()["APIC"];
            if(!pictures.isEmpty()) {
                TagLib::ID3v2::AttachedPictureFrame *tmp = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(pictures.front());
                size_t size = tmp->picture().size();
                pix.loadFromData((const unsigned char *)tmp->picture().data(),size,"JPEG");
                pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                picture->setPixmap(pix);
            }
            else {
                pix.load(":/default.png","PNG");
                pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                picture->setPixmap(pix);
            }
        }
        else {
            this->title->setText (tr("%1").arg (fileInfo.baseName()));
            pix.load(":/default.png","PNG");
            pix = pix.scaled(96,96,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            picture->setPixmap(pix);
        }

        player->play(path);
    }
    else {
        /*do nothing*/
    }

}

void Up::ePrevious() {
    emit previous();
}

void Up::ePlay() {
    player->play(NULL);
}

void Up::eNext() {
    emit next();
}

void Up::stateChanged(Phonon::State newstate) {
    switch(newstate) {
    case Phonon::PlayingState : {
        buttonPlayOrPause->setIcon(QIcon(":/24x24/pause.png"));
        break;
    }
    default : {
        buttonPlayOrPause->setIcon(QIcon(":/24x24/play.png"));
        break;
    }
    }
}
