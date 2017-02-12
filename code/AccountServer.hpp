#include "Server.hpp"
#include <string.h>
#include "Database.hpp"

static const int BUFFER_SIZE = 500;

typedef struct Credentials {
    std::string username;
    std::string password;
} Credentials;

class AccountServer : public Server {

private:

    Database myDatabase;

public:

    AccountServer(int port, const char *databaseName);

    void run() override;

    void get_username_and_password(char *data, Credentials *credentials);

    void insert_account_in_db(std::string username, std::string password);

    void attemptCreateAccount(std::string username, std::string password);

    void checkCredentials(std::string username, std::string password);
};
