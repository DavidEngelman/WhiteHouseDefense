#include "Server.hpp"
#include <string.h>
#include "Database.hpp"

static const int BUFFER_SIZE = 500;

typedef struct Credentials {
    std::string username;
    std::string password;
} Credentials;

typedef struct Command {
    std::string action;
    Credentials credentials;
};

/* Ceci serait peut être mieux, je ne suis pas sur...

typedef struct Command {
    std::string action;
    std::string username;
    std::string password;
};

 * */

class AccountServer : public Server {

private:

    Database myDatabase;

public:

    AccountServer(int port, const char *databaseName);

    void run() override;

    void insert_account_in_db(std::string username, std::string password);

    void attemptCreateAccount(std::string username, std::string password);

    void checkCredentials(std::string username, std::string password);

    void parse_command(char *data, Command *command);
};
