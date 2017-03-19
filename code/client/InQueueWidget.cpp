//
//

#include <QtWidgets/QVBoxLayout>
#include "InQueueWidget.hpp"

InQueueWidget::InQueueWidget(QWidget* parent) {

    QFont font("calibri",12);
    this->setParent(parent);
    this->setFixedSize(180,60);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::blue);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    QVBoxLayout* Vlayout = new QVBoxLayout;

    leaveQueuButton = new QHandPointerButton("LEAVE QUEUE", 160,25);
    inQueueText = new QLabel("In Queue...");
    inQueueText->setStyleSheet("color : white;");

    inQueueText->setFont(font);

    Vlayout->addWidget(inQueueText);
    Vlayout->addWidget(leaveQueuButton);
    Vlayout->setAlignment(inQueueText, Qt::AlignCenter);
    Vlayout->setAlignment(leaveQueuButton, Qt::AlignCenter);

    this->setLayout(Vlayout);

    connect(leaveQueuButton, SIGNAL(clicked()), this->parentWidget(), SLOT(leaveQueue()));

}
