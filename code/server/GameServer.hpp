
#include "Server.hpp"
#include "../common/GameState.hpp"
#include <string.h>


class GameServer : public Server {

public:
    GameState serverGamesSate;

    void getReceivedChanges();

    void parseCommands(changes); //je pense que c'est inutile avec notre class command

    //oui, je crois que une des deux fonction (soit getReceivedChanges, soit parseCommands) ne servira a rien
    // dans ma tete, la partie du code de la boucle principale qui s'occupe des commandes du client sera
    // qq chose de ce genre

    /*
     * while (1){
     *      TowerCommand (ou un truc du genre) command = getCommand();
     *      modifyMap(command);
     * }
     */


    void sendGameState(gameState);
};
