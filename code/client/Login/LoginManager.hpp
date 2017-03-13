#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "../NetworkedManager.hpp"
#include "LoginUI.hpp"
#include "../../common/Networking.h"
#include "../Main/MainManager.hpp"
#include "../../common/Credentials.h"
#include "../App.hpp"

class LoginUI;

class LoginManager : public NetworkedManager {

private:
	LoginUI* loginUI;
	Credentials loginCredentials;

	std::string attemptLogin(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
    void goToMain();

public:
	LoginManager(int port, App* my_app);
    virtual ~LoginManager();
	void run() override;
    void login();

	void goToWelcome();
};

#endif