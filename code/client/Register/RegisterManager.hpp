#ifndef __REGISTERMANAGER__
#define __REGISTERMANAGER__

#include "../NetworkedManager.hpp"
#include "RegisterUI.hpp"
#include "../../common/Networking.h"
#include "../../common/Credentials.h"
#include "../Login/LoginManager.hpp"
#include "../App.hpp"

class RegisterGUI;

class RegisterManager : public NetworkedManager {

private:
	RegisterUI *registerUI; // TODO: fix, it's a pointer so that it compiles
	RegisterGUI *registerGUI;
    Credentials toRegister;
    bool attemptRegister(Credentials credentials);
    bool checkCredentialsValidity(Credentials credentials);
    void goToLogin();

public:

	RegisterManager(int port, App* my_app);
	void run() override;
	void registerUser();
	void goToWelcome();
};

#endif
