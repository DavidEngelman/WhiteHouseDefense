#ifndef PROJET_WELCOMECONSOLEUI_H
#define PROJET_WELCOMECONSOLEUI_H

#include <string>
#include <iostream>
#include "../Abstract/AbstractConsoleUI.hpp"
#include "WelcomeUI.hpp"

class WelcomeConsoleUI : public WelcomeUI, public AbstractConsoleUI {

public:
    void display() override;
    int select();

};


#endif //PROJET_WELCOMECONSOLEUI_H
