#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map map;
	int seed;

public:

    GameUI();

	Position getPosBuyingTower();
	bool isBuyingTower();

    bool checkCoord(int x, int y);

	void display();
	void setSeed(int seed);
};

#endif