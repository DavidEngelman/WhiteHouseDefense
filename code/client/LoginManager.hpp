#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "NetworkedManager.hpp"
#include "LoginUI.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"
#include "../common/Credentials.h"
#include "App.hpp"

class LoginGUI;

class LoginManager : public NetworkedManager {

private:
	LoginUI loginUI;
	LoginGUI *loginGUI;
	Credentials loginCredentials;

	std::string attemptLogin(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
    void goToMainManager();

public:
	LoginManager(int port, App* my_app);
	void run() override;
    void login();
};

#endif