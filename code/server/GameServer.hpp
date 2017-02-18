
#include "Server.hpp"
#include <string.h>


class GameServer : public Server {

public:
	GameState serverGamesSate;

	void getReceivedChanges();

	void parseCommands(changes); //je pense que c'est inutile avec notre class command

	void sendGameState(gameState);
};
