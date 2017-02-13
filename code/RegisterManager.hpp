#include "Manager.h"
#include "RegisterUI.hpp"
#include "Networking.h"
#include "Credentials.h"

class RegisterManager: public Manager {

private:
	RegisterUI registerUI;
    Credentials toRegister;

public:

    RegisterManager() = default;

	bool attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
	void registerUser();
};
