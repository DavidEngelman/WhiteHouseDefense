#include <QtCore/QFile>
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