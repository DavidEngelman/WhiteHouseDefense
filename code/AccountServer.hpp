#include "Server.hpp"
#include <string.h>
#include "Database.hpp"
#include "Credentials.h"

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

    bool insert_account_in_db(Credentials credentials);

    bool attemptCreateAccount(Credentials credentials);

    bool checkCredentials(Credentials credentials);

    void send_error(int client_sock_fd);
    void send_success(int client_sock_fd);

    void parse_command(char *data, Command *command);

    void handle_login(Credentials credentials, int client_sock_fd);

    void handle_register(Credentials credentials, int client_sock_fd);
};
