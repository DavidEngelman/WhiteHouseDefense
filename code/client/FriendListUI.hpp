#ifndef FRIENDLISTUI_HPP
#define FRIENDLISTUI_HPP

#include <iostream>
#include "AbstractUI.hpp"

class FriendListUI : public AbstractUI {
	
public:
	void display();
	void displayFriendList(std::string friendlist, std::string command);
    int select();
	std::string askUsername();
};



#endif

