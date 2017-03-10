#ifndef PROFILEUI_HPP
#define PROFILEUI_HPP

#include <iostream>
#include "../Abstract/AbstractUI.hpp"


class ProfileUI : public AbstractUI {


public:
	void display();
	void displayProfile(std::string);
	std::string askUsername();
	int select();
};

#endif
