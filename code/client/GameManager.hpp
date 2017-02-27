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
#include <cstdlib>
#include <cctype>
#include <pthread.h>
#include <unistd.h>

class GameManager : public AbstractManager{ //Tmp : public (à supprimer après tests)

private:

    int server_socket;
    bool runningThread = false;
    pthread_t thr;
    int inputThread;
    GameState gameState;
    GameUI gameUI;
    std::string player_username;
    int player_id; // Je sais plus si les deux sont utiles je les met au cas ou
    int quadrant;
    unsigned int getMapSeedFromServer() const;

    void unSerializeGameState(char* serialized_gamestate);
    void unSerializePlayerStates(std::string serialized_playerstates);
    void unSerializePlayerState(std::string serialized_playerstate);
    void unSerializeTowers(std::string serialized_towers);
    void unSerializeTower(std::string serialized_tower);
    void unSerializeWaves(std::string serialized_waves);
    void unSerializeWave(std::string serialized_wave);
    void unSerializePNJ(std::string serialized_pnj, Wave* wave);

public:

    GameManager(char* ip_addr, int port, int socket, int id, std::string username, App* app);

    int getQuadrant() const;

    void placeTower();

    void displayWave();

    void come_back_to_menu();

    bool is_alive();

    void run();

    void *input_thread();

    static void* staticInputThread(void *self);

    bool checkValidity(Position towerPos);

    bool sendRequest(Position towerPos, std::string towerType);

    int getQuadrantFromServer();
};

#endif