#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtWidgets/QVBoxLayout>
#include "IconLabel.hpp"

IconLabel::IconLabel(int id, QString path_to_image) : id(id) {

    this->setPixmap(QPixmap(QUrl::fromLocalFile(QFileInfo(path_to_image).absoluteFilePath()).toString()));
    this->setCursor(Qt::PointingHandCursor);
    this->show();

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedInt()));

}

void IconLabel::clickedInt() {
    emit clicked(id);

}

void IconLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}


