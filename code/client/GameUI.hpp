#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"

class GameUI {


public:
	void getUserCommands();

	void draw(GameState gameState);

	void showNoInternetError();

	void display();
};

#endif