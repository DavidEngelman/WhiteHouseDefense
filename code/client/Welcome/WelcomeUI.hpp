//TODO: Mettre dans le Cmake !!!

#ifndef PROJET_WELCOMEUI_HPP
#define PROJET_WELCOMEUI_HPP

#include <string>
#include "WelcomeManager.hpp"
#include "../Abstract/AbstractUI.hpp"

class WelcomeManager;

class WelcomeUI : public virtual AbstractUI {

protected:
    WelcomeManager *manager;

public:
    WelcomeUI(WelcomeManager *manager) : manager(manager) {};

    virtual ~WelcomeUI() = default;

    virtual void display() = 0;

};

#endif // PROJET_WELCOMEUI_HPP
