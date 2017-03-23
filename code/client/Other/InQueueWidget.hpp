//
//

#ifndef PROJET_INQUEUEWIDGET_HPP
#define PROJET_INQUEUEWIDGET_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "QHandPointerButton.hpp"

class InQueueWidget : public QWidget{

    QLabel* inQueueText;
    QHandPointerButton* leaveQueuButton;

public:

    InQueueWidget(QWidget* parent);

};


#endif //PROJET_INQUEUEWIDGET_HPP
