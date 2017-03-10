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
	RegisterUI registerUI;
	RegisterGUI *registerGUI;
    Credentials toRegister;

public:

	RegisterManager(int port, App* my_app);

	bool attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void run() override;

};

#endif
