
#include "Server.hpp"
#include "../common/GameState.hpp"
#include "PendingMatch.h"
#include "PlayerConnection.hpp"


static const int NUM_PLAYERS = 4;

class GameServer : public Server {
private:
    GameState gameState;
    PlayerConnection playerConnections[NUM_PLAYERS];

    void sendGameStateToPlayer(PlayerConnection& connection);

public:
    GameState serverGamesSate;

    GameServer(int port);

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

    void sendGameStateToPlayer();




    void sendGameStateToPlayer(int socket_fd);
};
