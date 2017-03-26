#include "../Other/Server.hpp"
#include <string.h>
#include "Database.hpp"
#include "../../common/Other/Credentials.hpp"
#include "../Commands/LoginRegisterCommand.hpp"
#include "../Commands/UpdateStatsCommand.hpp"
#include "../../common/Other/Command.hpp"
#include "../Other/PlayerConnection.hpp"
#include <algorithm>
#include <thread>
#include <mutex>

#define ALREADY_CO "-2"

class AccountServer : public Server {

private:

    Database database;
    std::vector<PlayerConnection> connectedPlayers;
    std::mutex friendListMutex;

public:

    void *client_handler(int client_sock);

    const std::vector<PlayerConnection> &getConnectedPlayers() const;
    bool is_player_already_connected(PlayerConnection& player);
    void add_connected_player(PlayerConnection& player);
    void handle_exit(int player_id);

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



    void handle_login(Credentials credentials, int client_sock_fd);

    bool handle_register(Credentials credentials, int client_sock_fd);

    void handle_ranking(int client_sock_fd);
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
    bool cancelInvitation(std::string requester, std::string receiver);
    
    void handle_getFriendList(int client_sock_fd, std::string requester);
    void handle_getFriendRequests(int client_sock_fd, std::string requester);
    void handle_getPendingInvitations(int client_sock_fd, std::string requester);
    void handle_sendFriendRequest(int client_sock_fd, std::string requester, std::string toAdd);
    void handle_removeFriend(int client_sock_fd, std::string requester, std::string toRemove);
    void handle_acceptFriendRequest(int client_sock_fd, std::string requester, std::string toAccept );
    void handle_declineFriendRequest(int client_sock_fd, std::string requester, std::string toDecline);
    void handle_getStatus(int client_sock_fd, std::string requester);
    void handle_cancelInvitation(int client_sock_fd, std::string requester,std::string toCancel );


    void handle_accountUpdate(int client_sock_fd);

    void handle_changeUsername(std::string basic_string, int id, int client_socket);

    void handle_changePassword(std::string basic_string, int id);

    void handle_changeIcon(int basic_string, int id);
};
