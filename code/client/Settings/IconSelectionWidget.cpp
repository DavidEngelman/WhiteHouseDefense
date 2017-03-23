#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "IconSelectionWidget.hpp"
#include "../Other/IconLabel.hpp"

IconSelectionWidget::IconSelectionWidget(SettingsGUI* _parent) : parentS(_parent) {
    this->setFixedSize(300,200);
    this->setWindowTitle("Select a new Icon");
    this->setWindowModality(Qt::ApplicationModal);

    QGridLayout *gridLayout = new QGridLayout;


    IconLabel* icon1 = new IconLabel(0, "../../qt_ui/game_pictures/icons/0.jpg");
    IconLabel* icon2 = new IconLabel(1, "../../qt_ui/game_pictures/icons/1.jpg");
    IconLabel* icon3 = new IconLabel(2, "../../qt_ui/game_pictures/icons/2.jpg");
    IconLabel* icon4 = new IconLabel(3, "../../qt_ui/game_pictures/icons/3.jpg");

    gridLayout->addWidget(icon1, 0, 0);
    gridLayout->addWidget(icon2, 0, 1);
    gridLayout->addWidget(icon3, 1, 0);
    gridLayout->addWidget(icon4, 1, 1);

    QObject::connect(icon1, SIGNAL(clicked(int)), this, SLOT(handleIconChoice(int)));
    QObject::connect(icon2, SIGNAL(clicked(int)), this, SLOT(handleIconChoice(int)));
    QObject::connect(icon3, SIGNAL(clicked(int)), this, SLOT(handleIconChoice(int)));
    QObject::connect(icon4, SIGNAL(clicked(int)), this, SLOT(handleIconChoice(int)));

    this->setLayout(gridLayout);
    this->show();
}

void IconSelectionWidget::handleIconChoice (int choice){
    parentS->applyIconChange(std::to_string(choice));
    this->close();
    this->deleteLater();

}
