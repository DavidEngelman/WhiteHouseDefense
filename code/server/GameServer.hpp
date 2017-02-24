
#include "Server.hpp"
#include "../common/GameState.hpp"
#include "PendingMatch.h"
#include "PlayerConnection.hpp"
#include "../common/Strings.hpp"
#include "PlaceTowerCommand.h"
#include <time.h>


static const int NUM_PLAYERS = 4;

class GameServer : public Server {
private:
    GameState gameState;
    std::vector<PlayerConnection> playerConnections;

    void sendGameStateToPlayer(PlayerConnection &connection);

    void get_and_process_command(int client_socket_fd, char buffer[]);

    void addTowerInGameState(PlaceTowerCommand &command);

    bool isFinishedClassic();    //pour le mode classic
    bool isFinishedCoop();       //pour le mode par équipe
    bool isFinishedVsTime();     //pour le mode contre la montre

public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections);

    void getReceivedChanges();


    void processClientCommands();

    void sendGameStateToPlayers();

    void launchWave();

    void run();

    void handleEndOfGame();

    void sendEndToPlayer(PlayerConnection &connection);

};
