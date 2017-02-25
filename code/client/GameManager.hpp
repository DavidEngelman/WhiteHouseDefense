#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"
#include "NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"

#define WAVE 'w'
#define PLACING_TOWER "t"

class GameManager : public NetworkedManager{ //Tmp : public (à supprimer après tests)

private:
    GameState gameState;
    GameUI gameUI;
    std::string player_username;
    int player_id; // Je sais plus si les deux sont utiles je les met au cas ou
    char phase; // Phase de jeu (vague d'ennemis ou placement de tours)

    unsigned int getMapSeedFromServer() const;
public:
    GameManager(char* ip_addr, int port, int id, std::string username, App* app);

    void placeTower();

    void displayWave();

    void come_back_to_menu();

    void run();

};

#endif