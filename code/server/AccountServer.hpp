#include "Server.hpp"
#include <string.h>
#include "Database.hpp"
#include "../common/Credentials.h"
#include "LoginRegisterCommand.hpp"
#include "Command.hpp"
#include "PlayerConnection.hpp"
#include <algorithm>
#include <pthread.h>

#define ALREADY_CO "-2"

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
    std::vector<PlayerConnection> connectedPlayers;

public:

    void *client_handler(void *arg);

    const std::vector<PlayerConnection> &getConnectedPlayers() const;

    bool is_player_already_connected(PlayerConnection& player);

    void add_connected_player(PlayerConnection& player);

    AccountServer(int port, const char *databaseName);

    void run() override;

    void get_and_process_command(int client_socket_fd, char *message_buffer);

    bool insert_account_in_db(Credentials credentials);

    bool attemptCreateAccount(Credentials credentials);

    bool checkCredentials(Credentials credentials);

    void send_error(int client_sock_fd);
    void send_success(int client_sock_fd);
    void send_success_id(int client_sock_fd, int player_id);
    void send_already_connected_error(int client_sock);


    void parse_command(char *data, Command *command);

    bool handle_login(Credentials credentials, int client_sock_fd);

    bool handle_register(Credentials credentials, int client_sock_fd);

    bool handle_ranking(int client_sock_fd);
    std::vector<RankingInfos> getRanking();
    std::string vectorTostring(std::vector<RankingInfos> vect);
    std::string vectorTostring(std::vector<std::string> vect);

    PublicAccountInfos getPublicAccountInfos(std::string username);
    bool handle_profile(int client_sock_fd, std::string username);

    std::vector<std::string> getFriendList(std::string username);
    std::vector<std::string> getFriendRequests(std::string username);
    std::vector<std::string> getPendingInvitations(std::string username);

    bool removeFriend(std::string requester, std::string receiver);
    bool acceptFriendRequest(std::string requester, std::string receiver);
    bool sendFriendRequest(std::string requester, std::string receiver);
    bool declineFriendRequest(std::string requester, std::string receiver);
    
    bool handle_getFriendList(int client_sock_fd, std::string requester);
    bool handle_getFriendRequests(int client_sock_fd, std::string requester);
    bool handle_getPendingInvitations(int client_sock_fd, std::string requester);
    bool handle_sendFriendRequest(int client_sock_fd, std::string requester, std::string toAdd);
    bool handle_removeFriend(int client_sock_fd, std::string requester, std::string toRemove);
    bool handle_acceptFriendRequest(int client_sock_fd, std::string requester,std::string toAccept );
    bool handle_declineFriendRequest(int client_sock_fd, std::string requester, std::string toDecline);


};
