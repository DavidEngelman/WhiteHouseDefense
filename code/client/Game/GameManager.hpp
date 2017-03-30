#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../../common/Gamestate/GameState.hpp"
#include "../Other/NetworkedManager.hpp"
#include "GameManager.hpp"
#include "../../common/Other/Networking.hpp"
#include "../Main/MainManager.hpp"
#include "GameConsoleUI.hpp"
#include "../../common/Npc/MexicanPNJ.h"
#include "../../common/Npc/CommunistPNJ.h"
#include "../../common/Npc/MuslimPNJ.h"
#include "../../server/Other/Server.hpp"
#include "../../common/Other/Command.hpp"
#include "../../common/Tower/MissileTower.hpp"
#include "../../common/Tower/GunTower.hpp"
#include "../../common/Tower/SniperTower.hpp"
#include "../../common/Tower/ShockTower.hpp"
#include <cstdlib>
#include <cctype>
#include <pthread.h>
#include <unistd.h>

class GameUI;

class GameManager : public QObject, public AbstractManager {

Q_OBJECT

private:
    int server_socket;

    GameState *gameState;
    GameUI *gameUI;
    int quadrant;
    bool isSupporter;
    char server_msg_buff[BUFFER_SIZE];

    bool nukeSpellAvailable = true;
    bool freezeSpellAvailable = true;
    bool airStrikeAvailable = true;

public:
    bool isNukeSpellAvailable() const;

    bool isFreezeSpellAvailable() const;

private:

    unsigned int getMapSeedFromServer() const;

    void unSerializeGameState(char *seriarlizedGamestate);

    void unSerializePlayerStates(std::string serialized_playerstates);

    void unSerializePlayerState(std::string serialized_playerstate);

    void unSerializeTowers(std::string serialized_towers);

    void unSerializeTower(std::string serialized_tower);

    void unSerializeWaves(std::string serialized_waves);

    void unSerializeWave(std::string serialized_wave);

    void unSerializePNJ(std::string serialized_pnj, Wave *wave);

    bool checkValidity(Position towerPos, GameState &gamestate, std::string typeOfTower);

    void sendBuyRequest(Position towerPos, std::string towerType);

    void sendSellRequest(Position towerPos);

    int getQuadrantFromServer();

    void getInitialGameStateFromServer();

public:

    GameManager(int socket, App *app);

    GameManager(int socket, bool _isSupporter, App *app);

    void run();

    GameState &getGameState();

    int getQuadrant();

    bool placeGunTower(Position towerPos);

    bool placeSniperTower(Position towerPos);

    bool placeShockTower(Position towerPos);

    bool placeMissileTower(Position towerPos);

    bool sellTower(Position toSell);

    void sendMessageToPlayers(const std::string &message);

    bool upgradeTower(Position toUpgrade);

    void sendUpgradeRequest(Position towerPos);

    bool isTowerInPosition(GameState &gamestate, Position towerPos);

    std::string &getUsername() { return gameState->getPlayerStates()[quadrant].getUsername(); };

    void nuclearBombSpell();

    void sendNuclearRequest();

    void launchFreezeSpell();

    void launchAirStrike(int i);

    void launchAdSpell();

    void launchTeamHeal();

    void sendFreezeSpellRequest();

    std::string getWinner();

    bool isAirStikeAvailable();

    void sendAirStrikeRequest(int quadrant);

    void sendAdSpellRequest();

    const std::string getMode();

    void comeBackToMenu();

    bool isAlive();

    ~GameManager();

public slots:

    void updateMap();


    void sendTeamHealRequest(int quadrant);
};

#endif