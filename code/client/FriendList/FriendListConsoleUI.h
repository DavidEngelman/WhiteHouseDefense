//
// Created by macbookair on 19/03/17.
//

#ifndef FRIENDLISTCONSOLEUI_H
#define FRIENDLISTCONSOLEUI_H

#include "../Abstract/AbstractConsoleUI.hpp"
#include "FriendListUI.hpp"


class FriendListConsoleUI : public AbstractConsoleUI, public FriendListUI {
private:
    void displayMenu();
    void displayFriendList(std::string friendlist, std::string command);
    int select();
    std::string askUsername();
    void displayError();
public:

    FriendListConsoleUI(FriendListManager *manager);
    void display();
};


#endif //PROJET_FRIENDLISTCONSOLEUI_H
