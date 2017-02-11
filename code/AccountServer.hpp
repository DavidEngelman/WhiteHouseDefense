#include "Server.hpp"
#include <string.h>
#include "Database.hpp"

class AccountServer : public Server {

private:

	Database myDatabase;

public:

    AccountServer(int port, const char* databaseName);

    void run() override;

	std::vector<std::string> get_username_and_password (char* data);

	void insert_account_in_db(std::string username, std::string password);
	void attemptCreateAccount(std::string username, std::string password);

	void checkCredentials(std::string username, std::string password);
};
