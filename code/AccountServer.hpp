#include "Server.hpp"
#include <string.h>
#include "Database.hpp"

class AccountServer : public Server {

private:

	Database myDataBase;

public:

    AccountServer(int port);

    void run() override;

	std::vector<std::string> get_username_and_password (char* data);

	void attemptCreateAccount(std::string name, std::string password);

	void checkCredentials(std::string name, std::string password);
};
