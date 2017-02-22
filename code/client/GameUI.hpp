#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../common/GameState.hpp"
#include "../common/Map.hpp"


class GameUI {
private:
    Map map;

public:
    GameUI();

	std::string getCoordTower();

	void showNoInternetError();

	void display();

	std::string concatCoord(int x, int y);
};

#endif