#include <QtCore/QFileInfo>
#include <QtWidgets/QVBoxLayout>
#include "IconLabel.hpp"

IconLabel::IconLabel(int id, QString path_to_image) : id(id) {

    this->setPixmap(QPixmap(path_to_image));
    this->setCursor(Qt::PointingHandCursor);
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedInt()));

}

void IconLabel::clickedInt() {
    emit clicked(id);

}

void IconLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}


