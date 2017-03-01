#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map* map;

	bool checkCoord(int x, int y);

public:
    GameUI(unsigned seed);

	Position getPosBuyingTower();
	Position getPosSellingTower();
	int getChoice();

	void display(GameState& gameState);
	void displayPosingPhase();
	void displayTowerShop();

	void displayGameOver(GameState& gamestate);

	void displayPlayerInfos(GameState &gameState, int quadrant);
    void sortRanking(PlayerState players[]);
};

#endif