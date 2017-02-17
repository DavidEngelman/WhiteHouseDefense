#include "../common/GameState.hpp"

class GameUI {


public:
	void getUserCommands();

	void draw(GameState gameState);

	void showNoInternetError();

	void display();
};
