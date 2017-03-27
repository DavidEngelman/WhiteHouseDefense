#include <QtWidgets/QVBoxLayout>
#include <QMovie>
#include "InQueueWidget.hpp"

InQueueWidget::InQueueWidget(QWidget *parent) {

    QFont font("calibri", 12);
    this->setParent(parent);
    this->setFixedSize(250, 70);
    this->setStyleSheet("border: 2px solid white;");

    QVBoxLayout *Vlayout = new QVBoxLayout;
    QMovie *movie = new QMovie("../../qt_ui/game_pictures/backgrounds/particles_gold_bg.gif");
    this->setMovie(movie);
    movie->start();


    leaveQueuButton = new QHandPointerButton("LEAVE QUEUE");
    leaveQueuButton->setFixedSize(160, 25);
    leaveQueuButton->setStyleSheet(
            "background-color: rgba(0, 0, 0, 0); border-image:url(../../qt_ui/game_pictures/buttons/mainmenu.png);"
                    "color: black; border:1px solid white;");
    inQueueText = new QLabel("In Queue...");
    inQueueText->setStyleSheet("color : black; border: 0px solid white;");

    inQueueText->setFont(font);

    Vlayout->addWidget(inQueueText);
    Vlayout->addWidget(leaveQueuButton);
    Vlayout->setAlignment(inQueueText, Qt::AlignCenter);
    Vlayout->setAlignment(leaveQueuButton, Qt::AlignCenter);

    this->setLayout(Vlayout);

    connect(leaveQueuButton, SIGNAL(clicked()), this->parentWidget(), SLOT(leaveQueue()));

    this->show();

}


