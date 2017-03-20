
#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include "Server.hpp"
#include "../common/gamestate/GameState.hpp"
#include "PendingMatch.hpp"
#include "PlayerConnection.hpp"
#include "../common/Strings.hpp"
#include "TowerCommand.hpp"
#include "GameEngine.hpp"
#include <time.h>
#include "../common/Constants.hpp"
#include "../common/Tools.hpp"
#include <mutex>


class GameServer : public Server {

private:


    std::string mode;
    unsigned int mapSeed;

    GameEngine *gameEngine; // TODO: vu qu'on garde la mapSeed, ceci n'a plus besoin d'etre un pointeur
    std::vector<PlayerConnection> playerConnections;

    std::vector<int> supportersSockets;

    pthread_t spectatorJoinThread;
    pthread_t receiverThread;


    void sendGameStateToPlayer(PlayerConnection &connection);

    void sendGameStateToPlayer(int socket_fd);

    void addTowerInGameState(TowerCommand &command);


public:

    GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode);


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

    void removeClosedSocketFromSocketLists(int fd);

    void attemptSendMessageToClientSocket(int fd, const char *message);

    int getReadableReadableSocket(int timeLeft);

    bool socketIsActive(int fd);

    std::vector<PlayerConnection> &getPlayerConnections();

    void startInputThread();

    void stopInputThread();

    static void *staticInputThread(void *self);

    void getAndProcessPlayerInput();

    void getAndProcessUserInput(int clientSocketFd, char buffer[]);

    void sendMessageToOtherPlayers(std::string &userMessage, std::string &senderUsername);

    void handleEndOfGame();

    void tellSupportersTheGameIsOver();

    void processSpecialCommand(std::string &userMessage, std::string &senderUsername);

    std::string makeMessage(const std::string &userMessage, const std::string &senderUsername) const;
};

#endif