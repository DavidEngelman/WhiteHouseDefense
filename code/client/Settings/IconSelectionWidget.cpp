#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "IconSelectionWidget.hpp"

IconSelectionWidget::IconSelectionWidget(QWidget* _parent) : parent(_parent) {
    this->setFixedSize(300,200);
    this->setWindowTitle("Select a new Icon");
    this->setWindowModality(Qt::ApplicationModal);

    QGridLayout *gridLayout = new QGridLayout;

    QLabel *label_1 = new QLabel;
    label_1->setPixmap(QPixmap("../../qt_ui/game_pictures/icons/1.jpeg"));

    QLabel *label_2 = new QLabel;
    label_2->setPixmap(QPixmap("../../qt_ui/game_pictures/icons/2.jpg"));

    QLabel *label_3 = new QLabel;
    label_3->setPixmap(QPixmap("../../qt_ui/game_pictures/icons/5.jpg"));

    QLabel *label_4 = new QLabel;
    label_4->setPixmap(QPixmap("../../qt_ui/game_pictures/icons/6.jpg"));

    gridLayout->addWidget(label_1, 0, 0);
    gridLayout->addWidget(label_2, 0, 1);
    gridLayout->addWidget(label_3, 1, 0);
    gridLayout->addWidget(label_4, 1, 1);


    this->setLayout(gridLayout);
    this->show();




}
