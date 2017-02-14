#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "Manager.h"
#include "LoginUI.hpp"
#include "Networking.h"
#include "MainManager.hpp"
#include "Credentials.h"

class LoginManager : public Manager {

private:
	LoginUI loginUI;
	Credentials toLogin;

public:
	LoginManager(int port, char* address);
	bool attemptLogin(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void login_process();
};

#endif