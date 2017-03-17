#include <QtCore/QFile>
#include <QtMultimedia/QMediaPlaylist>
#include <QtCore/QFileInfo>
#include <QtMultimedia/QMediaPlayer>
#include "AbstractGUI.hpp"

void AbstractGUI::setStylesheetFromPath(QString stylesheetPath) {
    QFile File(stylesheetPath);
    File.open(QIODevice::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    setStyleSheet(styleSheet);
}

void AbstractGUI::setBackgroundFromPath(QString backgroundPath) {
    QPixmap backgroundImage(backgroundPath);
    backgroundImage = backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImage);
    setPalette(palette);
}

void AbstractGUI::destroy() {
    close();
    deleteLater();
}

void AbstractGUI::setMusicFromPath(QString musicPath) {
    QMediaPlayer *player = new QMediaPlayer(this);

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath()));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player->setVolume(100);
    player->setPlaylist(playlist);
    player->play();

}
