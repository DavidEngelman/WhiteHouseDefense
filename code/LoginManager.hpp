#include "Manager.h"

class LoginManager : public Manager {

private:
	LoginUI loginUI;

public:
	void attemptLogin(string name, string password);

	void checkCredentialsValidity(string name, string password);
};
