#ifndef PROFILE_CONSOLE_UI_HPP
#define PROFILE_CONSOLE_UI_HPP

#include <iostream>
#include "../Abstract/AbstractConsoleUI.hpp"
#include "ProfileUI.hpp"


class ProfileConsoleUI : public AbstractConsoleUI, public ProfileUI {
private:
    void displayMenu();
    void askUsername();

public:
    ProfileConsoleUI(ProfileManager *profileManager);

    void display() override;

    void displayNoSuchProfileError() override;

    void updateProfile() override;
};

#endif
