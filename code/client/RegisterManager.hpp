#ifndef __REGISTERMANAGER__
#define __REGISTERMANAGER__

#include "NetworkedManager.hpp"
#include "RegisterUI.hpp"
#include "../common/Networking.h"
#include "../common/Credentials.h"
#include "LoginManager.hpp"
#include "App.hpp"


class RegisterManager : public NetworkedManager {

private:
	RegisterUI registerUI;
    Credentials toRegister;

public:

	RegisterManager(int port, char* address);

	bool attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void registerUser();
	void run() override;

};

#endif
