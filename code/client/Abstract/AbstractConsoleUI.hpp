#ifndef PROJET_ABSTRACTCONSOLEUI_HPP
#define PROJET_ABSTRACTCONSOLEUI_HPP

#include "AbstractUI.hpp"

class AbstractConsoleUI: public virtual AbstractUI {
public:
    virtual void destroy() override {
        delete this;
    }
};

#endif //PROJET_ABSTRACTCONSOLEUI_HPP
