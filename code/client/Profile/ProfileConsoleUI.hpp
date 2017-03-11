#ifndef PROFILE_CONSOLE_UI_HPP
#define PROFILE_CONSOLE_UI_HPP

#include <iostream>
#include "../Abstract/AbstractUI.hpp"
#include "ProfileUI.hpp"


class ProfileConsoleUI : public AbstractUI, public ProfileUI {
private:
    void displayMenu();
    void askUsername();

public:
    ProfileConsoleUI(ProfileManager *profileManager);

    void display() override;

    void displayNoSuchProfileError() override;

    void displayProfile() override;
};

#endif
