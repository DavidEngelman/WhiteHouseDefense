//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_MAINGUI_HPP
#define PROJET_MAINGUI_HPP


#include "../Abstract/AbstractGUI.hpp"

class MainManager;

class MainGUI : public AbstractGUI {

public:
    void setupGUI();
    MainGUI(MainManager *manager);

private:
    MainManager *manager;
};


#endif //PROJET_MAINGUI_HPP
