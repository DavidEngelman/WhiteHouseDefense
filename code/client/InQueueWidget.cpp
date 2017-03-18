//
//

#include <QtWidgets/QVBoxLayout>
#include "InQueueWidget.hpp"

InQueueWidget::InQueueWidget(QWidget* parent) {
    this->setParent(parent);
    this->setFixedSize(220,90);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::blue);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    QVBoxLayout* Vlayout = new QVBoxLayout;

    leaveQueuButton = new QHandPointerButton("LEAVE QUEUE", 212,45);
    inQueueText = new QLabel("In Queue...");

    Vlayout->addWidget(inQueueText);
    Vlayout->addWidget(leaveQueuButton);
    Vlayout->setAlignment(inQueueText, Qt::AlignCenter);
    Vlayout->setAlignment(leaveQueuButton, Qt::AlignCenter);

    this->setLayout(Vlayout);

}
