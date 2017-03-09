#ifndef __REGISTERUI__
#define  __REGISTERUI__

#include <iostream>
#include <string>
#include "AbstractUI.hpp"

class RegisterUI : public AbstractUI {
	std::string username_entry;
	std::string password_entry;


public:
	RegisterUI();
	std::string get_username_entry() { return username_entry; };
	std::string get_password_entry() { return password_entry; };

	void ask_username();
	void ask_password();

	void display();
	void displayError();

};

#endif