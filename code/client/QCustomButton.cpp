//
// Created by titi on 12/03/17.
//

#include "QCustomButton.h"


void QCustomButton::clickedInt() {
    emit clicked(myNumber);
}

QCustomButton::QCustomButton(int number, QString text, QWidget *parent) : QPushButton(parent), myNumber(number) {
    setText(text);
    setCursor(Qt::PointingHandCursor);
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedInt()));
}