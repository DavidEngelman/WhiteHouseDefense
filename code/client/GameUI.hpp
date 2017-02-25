#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map& map;

public:
    GameUI(Map& map);

	Position getPosBuyingTower();
	bool isBuyingTower();

    bool checkCoord(int x, int y);

	void display(GameState& gameState);
};

#endif