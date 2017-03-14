#ifndef LOGIN_CONSOLE_HPP
#define LOGIN_CONSOLE_HPP

#include <string>
#include <iostream>
#include "../Abstract/AbstractConsoleUI.hpp"
#include "LoginUI.hpp"

class LoginConsoleUI : public LoginUI, public AbstractConsoleUI {
private:
	std::string username;
	std::string password;

public:
	void ask_username();
	void ask_password();

    LoginConsoleUI(LoginManager* manager);

	std::string getUsername() override;
	std::string getPassword() override;
	void display() override;
	void displayError() override;
	void displayAlreadyConnected() override;
};

#endif // LOGIN_CONSOLE_HPP
