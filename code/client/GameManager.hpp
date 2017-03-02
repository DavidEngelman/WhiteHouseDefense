#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../common/GameState.hpp"
#include "GameUI.hpp"
#include "NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../common/Networking.h"
#include "MainManager.hpp"
#include "../common/GunTower.hpp"
#include <cstdlib>
#include <cctype>
#include <pthread.h>
#include <unistd.h>

class GameManager : public AbstractManager{

private:
    int counter = 0;
    int server_socket;
    bool runningThread = false;
    pthread_t thr;
    int inputThread;
    GameState gameState;
    GameUI gameUI;
    int quadrant;
    bool isSupporter;

    unsigned int getMapSeedFromServer() const;
    void unSerializeGameState(char* serialized_gamestate);
    void unSerializePlayerStates(std::string serialized_playerstates);
    void unSerializePlayerState(std::string serialized_playerstate);
    void unSerializeTowers(std::string serialized_towers);
    void unSerializeTower(std::string serialized_tower);
    void unSerializeWaves(std::string serialized_waves);
    void unSerializeWave(std::string serialized_wave);
    void unSerializePNJ(std::string serialized_pnj, Wave* wave);

    static void* staticInputThread(void *self);
    void *input_thread();

    void come_back_to_menu();
    bool is_alive();
    bool isTowerInPosition(GameState &gamestate, Position towerPos);
    bool checkValidity(Position towerPos, GameState& gamestate);

    void sendBuyRequest(Position towerPos, std::string towerType);
    void sendSellRequest(Position towerPos);

    int getQuadrantFromServer();
    void getInitialGameStateFromServer();

public:

    GameManager(int socket, App* app);
    GameManager(int socket, bool _isSupporter, App *app);

    void run();
};

#endif