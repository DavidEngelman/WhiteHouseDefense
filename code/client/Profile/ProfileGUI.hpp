#ifndef PROJET_PROFILEGUI_HPP
#define PROJET_PROFILEGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "ProfileManager.hpp"
#include "ProfileUI.hpp"

class ProfileGUI : public AbstractGUI, public ProfileUI {
    ProfileManager *manager;


public:
    ProfileGUI(ProfileManager *manager);
    void display() override;

    void displayNoSuchProfileError() override;

    void displayProfile() override;
};


#endif //PROJET_PROFILEGUI_HPP
