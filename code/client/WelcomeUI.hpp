//
//

#ifndef PROJET_WELCOMEUI_H
#define PROJET_WELCOMEUI_H

#include <string>
#include <iostream>
#include "AbstractUI.hpp"


class WelcomeUI : public AbstractUI {

public:
    void display();
    int select();

};


#endif //PROJET_WELCOMEUI_H
