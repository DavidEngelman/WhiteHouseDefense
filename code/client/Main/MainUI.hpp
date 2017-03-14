#ifndef PROJET_MAINUI_HPP
#define PROJET_MAINUI_HPP

#include <string>
#include "MainManager.hpp"

class MainManager;

class MainUI: public AbstractUI {
protected:
    int menuChoice;
    int gameModeChoice;
    MainManager *manager;
public:
    MainUI(MainManager * manager): manager(manager), menuChoice(-1), gameModeChoice(-1) {};
    // NE PAS ENLEVER. FONDAMENTAL POUR ASSURER LA DESTRUCTION CORRECTE DES OBJETS;
    virtual ~MainUI() = default;
    virtual int getMenuChoice() { return menuChoice; };
    virtual int getGameModeChoice() { return gameModeChoice; }

    virtual void display() = 0;
    virtual void displayGameModesMenu() = 0;
};

#endif //PROJET_MAINUI_HPP
