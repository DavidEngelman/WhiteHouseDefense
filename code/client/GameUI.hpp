#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map map;

public:
    GameUI();

	void getUserCommands();

	void draw(GameState gameState);

	void showNoInternetError();

	void display();
};

#endif