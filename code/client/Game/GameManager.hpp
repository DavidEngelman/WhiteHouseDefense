#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../../common/gamestate/GameState.hpp"
#include "GameUI.hpp"
#include "../NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../../common/Networking.hpp"
#include "../Main/MainManager.hpp"
#include "../../common/tower/GunTower.hpp"
#include "../../common/tower/SniperTower.hpp"
#include "../../common/tower/ShockTower.hpp"
#include <cstdlib>
#include <cctype>
#include <pthread.h>
#include <unistd.h>

class GameUI;

class GameManager : public QObject, public AbstractManager{

    Q_OBJECT

private:
    int counter = 0;
    int server_socket;
    bool runningThread = false;
    pthread_t thr;
    int inputThread;
    GameState gameState;
    GameUI *gameUI;
    int quadrant;
    bool isSupporter;
    bool nukeSpell = true;

    QTimer *timer;


    unsigned int getMapSeedFromServer() const;
    void unSerializeGameState(char* seriarlizedGamestate);
    void unSerializePlayerStates(std::string serialized_playerstates);
    void unSerializePlayerState(std::string serialized_playerstate);
    void unSerializeTowers(std::string serialized_towers);
    void unSerializeTower(std::string serialized_tower);
    void unSerializeWaves(std::string serialized_waves);
    void unSerializeWave(std::string serialized_wave);
    void unSerializePNJ(std::string serialized_pnj, Wave* wave);

    void comeBackToMenu();
    bool is_alive();
    bool checkValidity(Position towerPos, GameState& gamestate, std::string typeOfTower);

    void sendBuyRequest(Position towerPos, std::string towerType);
    void sendSellRequest(Position towerPos);

    int getQuadrantFromServer();
    void getInitialGameStateFromServer();

public:

    GameManager(int socket, App* app);
    GameManager(int socket, bool _isSupporter, App *app);

    void run();

    GameState &getGameState();

    int getQuadrant();

    bool placeGunTower(Position towerPos);

    bool placeSniperTower(Position towerPos);

    bool placeShockTower(Position towerPos);

    bool sellTower(Position toSell);

    //void updateMap();

    void sendMessageToPlayers(const std::string &message);

    bool upgradeTower(Position toUpgrade);

    void sendUpgradeRequest(Position towerPos);

    bool isTowerInPosition(GameState &gamestate, Position towerPos);

    std::string &getUsername() { return gameState.getPlayerStates()[quadrant].getUsername(); };

    void nuclearBombSpell();

    void sendNuclearRequest();

public slots:
    void updateMap();
};

#endif