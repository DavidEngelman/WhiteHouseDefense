class GameServer : Server {

public:
	GameState serverGamesSate;

	void getReceivedChanges();

	void parseCommands(changes);

	void sendGameState(gameState);
};
