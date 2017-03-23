#ifndef MATCHMAKER_HPP
#define MATCHMAKER_HPP

#include "../Other/Server.hpp"
#include "PendingMatch.hpp"
#include "../Commands/MatchmakingCommand.hpp"
#include "../../common/Other/Strings.hpp"
#include "../Other/PlayerConnection.hpp"
#include "GameServer.hpp"
#include <thread>
#include "GameServer.hpp"

class MatchMaker : public Server {

private:

    PendingMatch classicPendingMatch;
    PendingMatch timedPendingMatch;
    PendingMatch teamPendingMatch;

    std::vector<GameServer *> activeGames;

    int current_server_port;

    void announceMatchStart(PlayerConnection playerConnection);
    void launchGameServer(PendingMatch match);
    void launchMatch(PendingMatch match);
    PendingMatch& getMatch(std::string mode);
    void addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode);
    void get_and_process_command(int socket_fd);

    void launchGameServerThread(PendingMatch& match);
public:

    MatchMaker(int port);

    void run() override;

    void handleRequestFromSpectator(int socket);

    void removeGameFromGamesInProgress(int port);

    void removePlayerFromQueue(std::string basic_string, int socket);

    void removePlayerFromMatch(PendingMatch &match, int socket);

    void *client_handler(int client);
};

#endif
