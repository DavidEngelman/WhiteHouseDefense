#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "Manager.h"
#include "LoginUI.hpp"
#include "Networking.h"

class LoginManager : public Manager {

private:
	LoginUI loginUI;

public:
	LoginManager(int port, char* adress);
	bool attemptLogin(std::string name, std::string password);
	void sendDataToServer(std::string name, std::string password);
	bool checkCredentialsValidity(std::string name, std::string password);
	void login_process();
};

#endif