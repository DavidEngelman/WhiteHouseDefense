#ifndef PROJET_ABSTRACTCONSOLEUI_HPP
#define PROJET_ABSTRACTCONSOLEUI_HPP

#include "AbstractUI.hpp"

class AbstractConsoleUI: public AbstractUI {
public:
    void destroy() override {
        delete this;
    }
};

#endif //PROJET_ABSTRACTCONSOLEUI_HPP
