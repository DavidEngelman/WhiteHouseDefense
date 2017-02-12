
#include <string>

class RegisterUI {


public:
	RegisterUI();
	std::string ask_username();
	std::string ask_password();
	void diplay();
	void displayError();
};
