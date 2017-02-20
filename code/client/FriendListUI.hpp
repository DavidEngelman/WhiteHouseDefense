#ifndef FRIENDLISTUI_HPP
#define FRIENDLISTUI_HPP

#include <iostream>

class FriendListUI {
	
public:
	void display();
	void displayFriendList(std::string friendlist, std::string command);
    int select();
	std::string askUsername();
};



#endif

