#ifndef PROJET_MAINUI_HPP
#define PROJET_MAINUI_HPP

#include <string>
#include "MainManager.hpp"

class MainUI: public virtual AbstractUI {

protected:
    int menuChoice;
    int gameModeChoice;
    MainManager *manager;

public:

    MainUI(MainManager * manager): manager(manager), menuChoice(-1), gameModeChoice(-1) {};


    virtual int getMenuChoice() { return menuChoice; };
    virtual int getGameModeChoice() { return gameModeChoice; }

    virtual void display() = 0;
    virtual void displayGameModesMenu() = 0;
    virtual void showInQueue() = 0;


    virtual ~MainUI() = default;
};

#endif //PROJET_MAINUI_HPP
