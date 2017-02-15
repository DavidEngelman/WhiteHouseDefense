#include "Server.hpp"
#include <string.h>
#include "Database.hpp"
#include "Credentials.h"
#include "LoginRegisterCommand.hpp"
#include "Command.hpp"

static const int BUFFER_SIZE = 500;

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

    void get_and_process_command(int client, char* message_buffer);

    bool insert_account_in_db(Credentials credentials);

    bool attemptCreateAccount(Credentials credentials);

    bool checkCredentials(Credentials credentials);

    void send_error(int client_sock_fd);
    void send_success(int client_sock_fd);

    void parse_command(char *data, Command *command);

    bool handle_login(Credentials credentials, int client_sock_fd);

    bool handle_register(Credentials credentials, int client_sock_fd);

    bool handle_ranking(int client_sock_fd);
    std::vector<RankingInfos> getRanking();

    std::string get_command_type(char* data);
};
