#ifndef PROJET_PROFILEUI_HPP
#define PROJET_PROFILEUI_HPP

#include "ProfileManager.hpp"

class ProfileManager;

class ProfileUI {
protected:
    int choice;
    std::string username;
    ProfileManager *profileManager;
public:
    ProfileUI(ProfileManager *profileManager) : profileManager(profileManager),
                                                choice(-1),
                                                username("Username not initialized") {};

    std::string getUsername() { return username; }

    virtual void display() = 0;

    virtual void displayNoSuchProfileError() = 0;

    virtual void displayProfile() = 0;
};

#endif //PROJET_PROFILEUI_HPP
