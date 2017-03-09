#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "NetworkedManager.hpp"
#include "LoginUI.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"
#include "../common/Credentials.h"
#include "App.hpp"
#include "LoginGUI.hpp"

class LoginManager : public NetworkedManager {

private:
	LoginUI loginUI;
	LoginGUI loginGUI;
	Credentials loginCredentials;

public:
	LoginManager(int port, App* my_app);
	std::string attemptLogin(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void run() override;
};

#endif