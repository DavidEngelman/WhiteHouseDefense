class GameServer : Server {

public:
	GameState serverGamesSate;

	void getReceivedChanges();

	void parseCommands(int changes);

	void sendGameState(int gameState);
};
