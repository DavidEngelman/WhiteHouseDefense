#include "Server.hpp"
#include <string.h>

class AccountServer : public Server {


public:

    AccountServer(int port);

    void run() override ;

	void attemptCreateAccount(std::string name, std::string password);

	void checkCredentials(std::string name, std::string password);
};
