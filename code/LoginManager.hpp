#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "Manager.h"
#include "LoginUI.hpp"

class LoginManager : public Manager {

private:
	LoginUI loginUI;

public:
	LoginManager();
	void attemptLogin(std::string name, std::string password);
	void sendDataToServer(std::string name, std::password);
	void checkCredentialsValidity(std::string name, std::string password);
	void login_process();
};

#endif