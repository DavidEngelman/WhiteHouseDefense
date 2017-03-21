#include "IconLabel.hpp"

IconLabel::IconLabel(int id, QString path_to_image) : id(id), label(new QLabel()) {

    label->setPixmap(QPixmap(path_to_image));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedInt()));

}

void IconLabel::clickedInt() {
    emit clicked(id);

}

IconLabel::~IconLabel() {
    delete label;
}

