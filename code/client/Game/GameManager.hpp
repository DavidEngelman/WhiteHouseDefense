#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../../common/Gamestate/GameState.hpp"
#include "GameUI.hpp"
#include "../Other/NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../../common/Other/Networking.hpp"
#include "../Main/MainManager.hpp"
#include "../../common/Tower/GunTower.hpp"
#include "../../common/Tower/SniperTower.hpp"
#include "../../common/Tower/ShockTower.hpp"
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

    GameState gameState;
    GameUI *gameUI;
    int quadrant;
    bool isSupporter;

    bool nukeSpellAvailable = true;
    bool freezeSpellAvailable = true;
    bool airStrikeAvailable = true;

    QTimer *timer;

public:
    bool isNukeSpellAvailable() const;

    bool isFreezeSpellAvailable() const;

private:


    unsigned int getMapSeedFromServer() const;
    void unSerializeGameState(char* seriarlizedGamestate);
    void unSerializePlayerStates(std::string serialized_playerstates);
    void unSerializePlayerState(std::string serialized_playerstate);
    void unSerializeTowers(std::string serialized_towers);
    void unSerializeTower(std::string serialized_tower);
    void unSerializeWaves(std::string serialized_waves);
    void unSerializeWave(std::string serialized_wave);
    void unSerializePNJ(std::string serialized_pnj, Wave* wave);

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

    bool placeMissileTower(Position towerPos);

    void comeBackToMenu();

    bool isAlive();

    ~GameManager();

public slots:
    void updateMap();

    void launchFreezeSpell();

    void sendFreezeSpellRequest();


    std::string getWinner();

    void launchAirStrike(int i);

    bool isAirStikeAvailable();

    void sendAirStrikeRequest(int quadrant);

    void launchAdSpell();

    void sendAdSpellRequest();
};

#endif