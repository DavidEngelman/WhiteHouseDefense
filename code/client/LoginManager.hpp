#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "NetworkedManager.hpp"
#include "LoginUI.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"
#include "../common/Credentials.h"

class LoginManager : public NetworkedManager {

private:
	LoginUI loginUI;
	Credentials loginCredentials;

public:
	LoginManager(int port, char* address);
	std::string attemptLogin(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void login_process();
};

#endif