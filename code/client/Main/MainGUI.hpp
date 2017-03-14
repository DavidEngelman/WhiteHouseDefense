#ifndef PROJET_MAINGUI_HPP
#define PROJET_MAINGUI_HPP

#include "../Abstract/AbstractGUI.hpp"
#include "MainUI.hpp"

class MainGUI : public AbstractGUI, public MainUI {

public:
    MainGUI(MainManager *manager);
    virtual ~MainGUI() = default; // TODO: a implementer
    void display() override;
    void displayGameModesMenu() override;

    void handleMenuChoice();
    void handleGameModeChoice();
};


#endif //PROJET_MAINGUI_HPP
