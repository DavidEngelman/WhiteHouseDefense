#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"

class GameManager {

private:
    GameState playerGameState;
    GameUI gameUI;

public:
    void sendUserCommands();

    void getReceivedChanges();
};

#endif