#include "Manager.h"

class RegisterManager: public Manager {

private:
	RegisterUI registerUI;

public:

    RegisterManager() = default;

	void attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
};
