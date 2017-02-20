#ifndef PROFILEUI_HPP
#define PROFILEUI_HPP

#include <iostream>


class ProfileUI {


public:
	void display();
	void displayProfile(std::string);
	std::string askUsername();
	int select();
};

#endif
