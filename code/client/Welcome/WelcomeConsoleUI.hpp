#ifndef PROJET_WELCOMECONSOLEUI_H
#define PROJET_WELCOMECONSOLEUI_H

#include <string>
#include <iostream>
#include "../Abstract/AbstractConsoleUI.hpp"
#include "WelcomeUI.hpp"

class WelcomeConsoleUI : public WelcomeUI, public AbstractConsoleUI {

public:
    WelcomeConsoleUI(WelcomeManager *manager);

    void display() override;

    int select();
    void handleSelect(int choice);

};


#endif //PROJET_WELCOMECONSOLEUI_H
