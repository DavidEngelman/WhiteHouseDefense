
#include <iostream>
#include "../Abstract/AbstractUI.hpp"

#ifndef MAINUI_HPP
#define MAINUI_HPP

class MainUI : public AbstractUI {


public:
	void display();
	int select();

	void displayGameModes();
    int selectGameModeInt();
};

#endif