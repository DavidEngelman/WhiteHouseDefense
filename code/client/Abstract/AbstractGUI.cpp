#include <QtCore/QFile>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QtGui/QWindow>
#include "AbstractGUI.hpp"

AbstractGUI::AbstractGUI(QWidget* _parent) : parent(_parent) {
    setParent(parent);
}


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
    if (parent != nullptr) {
        parent->setPalette(palette);
    }else{
        this->setPalette(palette);
    }
}

void AbstractGUI::destroy() {
    close();
    deleteLater();
}

