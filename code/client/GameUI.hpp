#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map* map;

public:
    GameUI(unsigned seed);

	Position getPosBuyingTower();
	Position getPosSellingTower();
	int getChoice();
	bool isBuyingTower();
    bool checkCoord(int x, int y);
	void display(GameState& gameState);
};

#endif