#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"
#include "NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"
#include "../common/AttackTower.hpp"
#include "../common/SlowTower.hpp"
#include <thread>
#include <cstdlib>

class GameManager : public AbstractManager{ //Tmp : public (à supprimer après tests)

private:


    bool stopflag;
    int server_socket;
    GameState gameState;
    GameUI gameUI;
    std::string player_username;
    int player_id; // Je sais plus si les deux sont utiles je les met au cas ou
    int quadrant;

    unsigned int getMapSeedFromServer() const;

    void unSerializeGameState(char* serialized_gamestate);

public:

    GameManager(char *ip_addr, int port, int socket, int id, std::string username, App *app);

    int getQuadrant() const;

    void placeTower();

    void displayWave();

    void come_back_to_menu();

    bool is_alive();

    void run();

    void input_thread();

    bool checkValidity(Position towerPos);

    bool sendRequest(Position towerPos, std::string towerType);

    int getQuadrantFromServer();
};

#endif