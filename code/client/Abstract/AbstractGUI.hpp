#ifndef PROJET_ABSTRACTGUI_HPP
#define PROJET_ABSTRACTGUI_HPP


#include <QtWidgets/QWidget>
#include <iostream>
#include "AbstractUI.hpp"

class AbstractGUI : public QWidget, public AbstractUI {
public:
    virtual void display() = 0; // MUST BE IMPLEMENTED IN INHERITORS

    // NE PAS ENLEVER. FONDAMENTAL POUR ASSURER LA DESTRUCTION CORRECTE DES OBJETS;
    virtual ~AbstractGUI() {}
};


#endif //PROJET_ABSTRACTGUI_HPP
