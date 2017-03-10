#include <string>
#include <iostream>
#include "../Abstract/AbstractUI.hpp"

class LoginUI : public AbstractUI {

private:

	std::string username_entry;
	std::string password_entry;

public:
	std::string get_username_entry() { return username_entry; };
	std::string get_password_entry() { return password_entry; };
	void ask_username();
	void ask_password();
	void display();
	void displayError();
	void display_already_co_message();
};
