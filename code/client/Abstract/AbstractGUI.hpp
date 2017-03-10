//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_ABSTRACTGUI_HPP
#define PROJET_ABSTRACTGUI_HPP


#include <QtWidgets/QWidget>
#include "AbstractUI.hpp"

class AbstractGUI : public QWidget, public AbstractUI {
public:
    virtual void display() = 0; // MUST BE IMPLEMENTED IN INHERITORS
};


#endif //PROJET_ABSTRACTGUI_HPP
