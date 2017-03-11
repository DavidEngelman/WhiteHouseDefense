//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_PROFILEGUI_HPP
#define PROJET_PROFILEGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "ProfileManager.hpp"

class ProfileGUI : public AbstractGUI {
    ProfileManager *manager;


public:
    ProfileGUI(ProfileManager *manager);
    void display() override;

};


#endif //PROJET_PROFILEGUI_HPP
