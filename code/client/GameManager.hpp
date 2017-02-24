#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"
#include "NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"

class GameManager : NetworkedManager{

private:
    GameState gameState;
    GameUI gameUI;
    std::string player_username;
    int player_id; // Je sais plus si les deux sont utiles je les met au cas ou

public:
    GameManager(char* ip_addr, int port, int id, std::string username, App* app);

    void placeTower();

    void displayWave();

    void come_back_to_menu();

};

#endif