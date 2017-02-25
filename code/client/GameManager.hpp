#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"
#include "NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"

class GameManager : public NetworkedManager{ //Tmp : public (à supprimer après tests)

private:
    GameState gameState;
    GameUI gameUI;
    std::string player_username;
    int player_id; // Je sais plus si les deux sont utiles je les met au cas ou
    int quadrant;
    char phase[1]; // Phase de jeu (vague d'ennemis ou placement de tours)

    unsigned int getMapSeedFromServer() const;

    void unSerializeGameState(char* serialized_gamestate);

public:

    GameManager(char* ip_addr, int port, int id, std::string username, App* app);

    int getQuadrant() const;

    void placeTower();

    void displayWave();

    void come_back_to_menu();

    bool is_alive();

    void run();

    int getQuadrantFromServer();
};

#endif