
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "../common/GameState.hpp"
#include "PendingMatch.h"
#include "PlayerConnection.hpp"
#include "../common/Strings.hpp"
#include "PlaceTowerCommand.h"
#include "GameEngine.hpp"
#include <time.h>
#include "../common/Constants.h"

static const int NUM_PLAYERS = 4;

static const int NUM_SECONDS_TO_PLACE_TOWER = 60;
static const int INTERVAL_BETWEEN_SENDS_IN_MS = 200;

class   GameServer : public Server {
private:
    // Je l'ai mis comme pointeur, car je veux seulement l'initialiser dans la methode run.
    // Si je l'initialise dans le constructeur, je suis obligé de garder la seed dans un field
    // pour l'envoyer au client (pendant la methode run), ce que je veux éviter
    GameEngine * gameEngine;
    std::vector<PlayerConnection> playerConnections;
    int client_sockets[4];

    void sendGameStateToPlayer(PlayerConnection &connection);

    void get_and_process_command(int client_socket_fd, char buffer[]);

    void addTowerInGameState(PlaceTowerCommand &command);

    bool isFinishedClassic();    //pour le mode classic
    bool isFinishedCoop();       //pour le mode par équipe
    bool isFinishedVsTime();     //pour le mode contre la montre

public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections);

    void getReceivedChanges();


    void processClientCommands();

    void sendGameStateToPlayers();

    void runWave();

    void run();

    void handleEndOfGame();

    void sendEndToPlayer(PlayerConnection &connection);

    void sendWinnerToPlayer(PlayerConnection &connection);
    void sendMapSeedToClients(unsigned int mapSeed);

    void sendTowerPhase();
    void sendWavePhase();

    void SendQuadrantToClients();

    void createPlayerStates() const;
};

#endif