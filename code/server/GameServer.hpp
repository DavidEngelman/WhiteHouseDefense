
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
    PlayerConnection playerConnections[NUM_PLAYERS];

    void sendGameStateToPlayer(PlayerConnection &connection);

    void get_and_process_command(int client_socket_fd, char buffer[]);

    void addTowerInGameState(PlaceTowerCommand &command);

public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections);

    void getReceivedChanges();

    //je pense que c'est inutile avec notre class command
//    void parseCommands(changes);

    //oui, je crois que une des deux fonction (soit getReceivedChanges, soit parseCommands) ne servira a rien
    // dans ma tete, la partie du code de la boucle principale qui s'occupe des commandes du client sera
    // qq chose de ce genre

    /*
     * while (1){
     *      TowerCommand (ou un truc du genre) command = getCommand();
     *      modifyMap(command);
     * }
     */

    void processClientCommands();

    void sendGameStateToPlayers();

    // TODO: trouver un meilleur nom, celui ci n'est pas genial
    void runWave();

    void run();
};
