
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "../common/GameState.hpp"
#include "PendingMatch.h"
#include "PlayerConnection.hpp"
#include "../common/Strings.hpp"
#include "TowerCommand.h"
#include "GameEngine.hpp"
#include <time.h>
#include "../common/Constants.h"
#include "../common/Tools.hpp"
#include <mutex>




class GameServer : public Server {

private:


    std::string mode;
    unsigned int mapSeed;

    // Je l'ai mis comme pointeur, car je veux seulement l'initialiser dans la methode run.
    // Si je l'initialise dans le constructeur, je suis obligé de garder la seed dans un field
    // pour l'envoyer au client (pendant la methode run), ce que je veux éviter

    GameEngine * gameEngine;
    std::vector<PlayerConnection> playerConnections;
    int client_sockets[4];
    std::vector<int> supportersSockets;

    pthread_t spectatorJoinThread;



    void sendGameStateToPlayer(PlayerConnection &connection);
    void sendGameStateToPlayer(int socket_fd);
    void get_and_process_command(int client_socket_fd, char buffer[]);
    void addTowerInGameState(TowerCommand &command);


public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode);

    void processClientCommands();

    void sendGameStateToPlayers();

    void runWave();

    void run();

    void sendTowerPhase();
    void sendWavePhase();

    void createPlayerStates();

    int connectToServer(int port);
    void updatePlayerStatsOnAccountServer();

    void deleteTowerInGameState(TowerCommand command);

    void upgradeTowerInGameState(TowerCommand command);

    void runGame();

    void startSpectatorThread();

    void stopSpectatorThread();

    static void *staticJoinSpectatorThread(void *);

    void getAndProcessSpectatorJoinCommand();

    std::string getAllPlayers();

    std::string getMode();

    PlayerState &getPlayerStateWithUsername(std::string username);


    void setupGameForPlayers();

    void sendSetupGameStringToClient(int fd);

    void sendMapSeedToClient(int socket_fd);

    int getQuadrantForPlayer(std::string username);

    void sendQuadrantToClient(int socket_fd, int quadrant);

    void setupGameForPlayer(int player_socket_fd, int quadrant);

    void sendFinishedToMatchmaker();

    void endConnection(int fd);

    void attempt_send_message(int fd, const char* message);

    int getReadableReadableSocket(int timeLeft);

    bool socketIsActive(int fd);
};

#endif