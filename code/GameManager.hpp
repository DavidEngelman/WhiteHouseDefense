class GameManager {

private:
	GameState playerGameState;
	GameUI gameUI;

public:
	void sendUserCommands();

	void getReceivedChanges();
};
