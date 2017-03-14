#ifndef MAINCONSOLEUI_HPP
#define MAINCONSOLEUI_HPP

#include <iostream>
#include "../Abstract/AbstractUI.hpp"
#include "MainUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"

class MainConsoleUI : public AbstractConsoleUI, public MainUI {
public:
    MainConsoleUI(MainManager *manager);
    virtual ~MainConsoleUI() = default;

    void display() override;
    void displayGameModesMenu() override;

    void displayGameModeChoices() const;
    void displayMenuChoices() const;
};

#endif