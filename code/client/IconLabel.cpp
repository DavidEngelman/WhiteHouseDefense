#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtWidgets/QVBoxLayout>
#include "IconLabel.hpp"

IconLabel::IconLabel(int id, QString path_to_image, IconSelectionWidget* parentS) : id(id), label(new QLabel) {


    label->setPixmap(QPixmap(QUrl::fromLocalFile(QFileInfo(path_to_image).absoluteFilePath()).toString()));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedInt()));

    this->setCursor(Qt::PointingHandCursor);
    this->setParent(parentS);
    this->show();

}

void IconLabel::clickedInt() {
    emit clicked(id);

}

void IconLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

IconLabel::~IconLabel() {
    delete label;
}

