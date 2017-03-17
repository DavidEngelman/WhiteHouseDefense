#include <csignal>
#include "GameServer.hpp"
#include "../common/GunTower.hpp"
#include "../common/SniperTower.hpp"
#include "../common/ShockTower.hpp"

const bool DEBUG = false;

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode) :
        Server(port), playerConnections(playerConnections), mode(_mode), mapSeed((unsigned int) time(0)) {
}

void GameServer::run() {
    startSpectatorThread();
    startInputThread();
    runGame();
    stopSpectatorThread();
    stopInputThread();
    sendFinishedToMatchmaker(); // tell to the matchmaker that the game is finished
}

void GameServer::runGame() {

    start_socket_listen();
    sleep(3); // TODO: find better way to avoid network race conditions...
    gameEngine = new GameEngine(mapSeed, mode);

    // Creer les playerState
    createPlayerStates();

    if (!DEBUG) {
        setupGameForPlayers();
    }

    while (!gameEngine->isGameFinished()) {
        if (!DEBUG) {

            gameEngine->getTimerSinceGameStart().pause(); // peut etre faire ca juste en mode contre la montre
            sendTowerPhase();
            sleep(NUM_SECONDS_TO_PLACE_TOWER);
            gameEngine->getTimerSinceGameStart().resume(); // peut etre faire ca juste en mode contre la montre
            sendWavePhase();
        }
        runWave();
    }

    //gameEngine->declareWinner();
    updatePlayerStatsOnAccountServer();
    delete gameEngine;


    //handleEndOfGame();
}

/*
 * GAME EVOLUTION AND UPDATE; COMMUNICATION WITH CLIENT
 */

void GameServer::runWave() {
    Timer timer;
    timer.start();
    gameEngine->createWaves();
    bool isWaveFinished = false;
    while (!isWaveFinished) {
        while (!isWaveFinished && timer.elapsedTimeInMiliseconds() < INTERVAL_BETWEEN_SENDS_IN_MS) {
            isWaveFinished = gameEngine->update();
            usleep(100); // Pour eviter d'appeller update des tonnes de fois par tick. C'est en microsecondes
        }

        if (DEBUG) {
            gameEngine->showMap();
            // TODO: updateMap()
        } else {
            sendGameStateToPlayers();
        }
        timer.reset();
    }
}


void GameServer::sendGameStateToPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendGameStateToPlayer(playerConnections[i]);
    }

    for (int socketFd: supportersSockets) {
        sendGameStateToPlayer(socketFd);
    }
}


/*
 * Thread that processes user input (chat + place towers)
 */

void GameServer::startInputThread() {
    pthread_create(&receiverThread, NULL, &GameServer::staticInputThread, this);
}

void GameServer::stopInputThread() {
    pthread_cancel(receiverThread);
}

void *GameServer::staticInputThread(void * self) {
    static_cast<GameServer *>(self)->getAndProcessPlayerInput();
    return nullptr;
}

void GameServer::getAndProcessPlayerInput() {
    char messageBuffer[BUFFER_SIZE];
    while(1) {
        // TODO: the 10000 is absurdly high, not sure it's a good idea
        int clientSocketFd = getReadableReadableSocket(10000);
        getAndProcessUserInput(clientSocketFd, messageBuffer);
    }
}

void GameServer::getAndProcessUserInput(int clientSocketFd, char *buffer) {
    if (receive_message(clientSocketFd, buffer) != -1) {
        std::string command_type = get_command_type(buffer);

        if (command_type == PLACE_TOWER_COMMAND_STRING) {
            TowerCommand command;
            command.parse(buffer);
            addTowerInGameState(command);
        } else if (command_type == DELETE_TOWER_COMMAND_STRING) {
            TowerCommand command;
            command.parse(buffer);
            deleteTowerInGameState(command);
        } else if (command_type == UPGRADE_TOWER_COMMAND_STRING) {
            TowerCommand command;
            command.parse(buffer);
            upgradeTowerInGameState(command);
        } else if (command_type == USER_MESSAGE_STRING){
            Command command;
            command.parse(buffer);
            std::string userMessage = command.getNextToken();
            sendMessageToOtherPlayers(userMessage, clientSocketFd);
        }
    } else {
        removeClosedSocketFromSocketLists(clientSocketFd);
    }
}

void GameServer::sendMessageToOtherPlayers(std::string userMessage, int senderSocketFd) {
    std::string message = RECEIVE_USER_MESSAGE_STRING + "," + userMessage + ";";
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        if (socketFd != senderSocketFd) {
            send_message(socketFd, message.c_str());
        }
    }
}

int GameServer::getReadableReadableSocket(int timeLeft) {
    // TODO: solution temporaire. C'est debile de creer des vecteurs à chaque appel
    std::vector<int> open_sockets;
    for (PlayerConnection &playerConnection: playerConnections) {
        open_sockets.push_back(playerConnection.getSocketFd());
    }
    int socketIndex = get_readable_socket_index_with_timeout(open_sockets.data(), open_sockets.size(), timeLeft);
    return open_sockets[socketIndex];
}

void GameServer::addTowerInGameState(TowerCommand &command) {
    AbstractTower *tower;
    if (command.getTowerType() == GUN_TOWER_STR) {
        tower = new GunTower(command.getPosition());
    } else if (command.getTowerType() == SNIPER_TOWER_STR) {
        tower = new SniperTower(command.getPosition());
    } else {
        tower = new ShockTower(command.getPosition());
    }

    int quadrant = command.getPlayerQuadrant();
    gameEngine->addTower(tower, quadrant);
}

void GameServer::deleteTowerInGameState(TowerCommand command) {
    Position position = command.getPosition();
    int quadrant = command.getPlayerQuadrant();
    gameEngine->deleteTower(position, quadrant);
}


void GameServer::upgradeTowerInGameState(TowerCommand command) {
    Position position = command.getPosition();
    int quadrant = command.getPlayerQuadrant();
    gameEngine->upgradeTower(position, quadrant);

}


void GameServer::createPlayerStates() {
    if (gameEngine->getGameState().getMode() == TEAM_MODE) {
        gameEngine->addPlayerState(playerConnections[0].getPlayer_id(), playerConnections[0].getUsername(), 1);
        gameEngine->addPlayerState(playerConnections[1].getPlayer_id(), playerConnections[1].getUsername(), 1);
        gameEngine->addPlayerState(playerConnections[2].getPlayer_id(), playerConnections[2].getUsername(), 2);
        gameEngine->addPlayerState(playerConnections[3].getPlayer_id(), playerConnections[3].getUsername(), 2);
    } else {
        for (int i = 0; i < 4; ++i) {
            gameEngine->addPlayerState(playerConnections[i].getPlayer_id(), playerConnections[i].getUsername());
        }
    }

}






/*
 * THREAD THAT ADDS SUPPORTERS TO THE GAME
 */



void GameServer::startSpectatorThread() {
    pthread_create(&spectatorJoinThread, NULL, &GameServer::staticJoinSpectatorThread, this);
}

void GameServer::stopSpectatorThread() {
    pthread_cancel(spectatorJoinThread);
}

void *GameServer::staticJoinSpectatorThread(void *self) {
    static_cast<GameServer *>(self)->getAndProcessSpectatorJoinCommand();
    return nullptr;
}

void GameServer::getAndProcessSpectatorJoinCommand() {
    while (1) {
        int client_socket_fd = accept_connection();
        if (client_socket_fd == -1) {
            continue;
        }
        char command_buffer[BUFFER_SIZE];
        receive_message(client_socket_fd, command_buffer);

        /* Structure of command: "SUPPORT_PLAYER_STRING,bob;" */
        Command command;
        command.parse(command_buffer);

        if (command.getAction() == SUPPORT_PLAYER_STRING) {

            std::string username = command.getNextToken();
            std::cout << "New spectator for " << username << std::endl;
            PlayerState &playerState = getPlayerStateWithUsername(username);
            playerState.setIsSupported(true);
            setupGameForPlayer(client_socket_fd, getQuadrantForPlayer(username));

            // It's after the setup, because the supporter must first receive the game info before getting
            // treated in the main loop
            // TODO: peut etre utiliser ici un mutex pour éviter des problemes de coherence
            supportersSockets.push_back(client_socket_fd);
        }
    }
}

std::string GameServer::getMode() {
    return mode;
}

PlayerState &GameServer::getPlayerStateWithUsername(std::string username) {
    for (PlayerState &playerState: gameEngine->getGameState().getPlayerStates()) {
        if (playerState.getUsername() == username) {
            return playerState;
        }
    }
}

int GameServer::getQuadrantForPlayer(std::string username) {
    int quadrant = 0;
    for (PlayerConnection &playerConnection: playerConnections) {
        if (playerConnection.getUsername() == username) {
            return quadrant;
        }
        quadrant++;
    }
}

std::string GameServer::getAllPlayers() {
    std::string res = "";
    int count = 1;

    for (auto &pc : playerConnections) {

        res += pc.getUsername();
        res += count == playerConnections.size() ? ";" : ",";
        count++;
    }
    return res;
}

void GameServer::setupGameForPlayers() {
    unsigned int quadrant = 0;
    for (PlayerConnection &playerConnection: playerConnections) {
        int player_socket_fd = playerConnection.getSocketFd();
        setupGameForPlayer(player_socket_fd, quadrant);
        quadrant++;
    }
}

void GameServer::setupGameForPlayer(int player_socket_fd, int quadrant) {
    sendSetupGameStringToClient(player_socket_fd);
    sendMapSeedToClient(player_socket_fd);
    sendQuadrantToClient(player_socket_fd, quadrant);
    sendGameStateToPlayer(player_socket_fd);
}

/*
 * COMMUNICATION WITH CLIENT AND OTHER SERVERS
 */

void GameServer::sendTowerPhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        attemptSendMessageToClientSocket(socketFd, "t");
    }

    for (int socketFd: supportersSockets) {
        attemptSendMessageToClientSocket(socketFd, "t");
    }
}

void GameServer::sendWavePhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        attemptSendMessageToClientSocket(socketFd, "w");
    }

    for (int socketFd: supportersSockets) {
        attemptSendMessageToClientSocket(socketFd, "w");
    }
}

int GameServer::connectToServer(int port) {
    return init_connection_to_server((char *) "127.0.0.1", port); //Faudrait mettre des constantes :)

}

void GameServer::sendFinishedToMatchmaker() {
    int matchmaker_server_socket = connectToServer(5556);
    std::string message = "PopGame," + std::to_string(port) + ";";
    send_message(matchmaker_server_socket, message.c_str());
}

void GameServer::updatePlayerStatsOnAccountServer() {
    int account_server_socket = connectToServer(5555);
    int p_id, pnj_killed;
    bool is_winner;

    send_message(account_server_socket, "Update;");

    for (PlayerState &ps : gameEngine->getGameState().getPlayerStates()) {
        p_id = ps.getPlayer_id();
        pnj_killed = ps.getPnjKilled();
        is_winner = ps.getIsWinner();

        std::string message = "Update," + std::to_string(p_id) + "," + std::to_string(pnj_killed) + "," +
                              bool_to_string(is_winner) + ";";

        send_message(account_server_socket, message.c_str());
    }
}


void GameServer::sendSetupGameStringToClient(int socket_fd) {
    send_message(socket_fd,
                 SETUP_GAME); // Ici j'ai du remettre Send_message pcq sinon quand on envoyait le setupGame a un Spectater, ca ne fonctionnait pas car a ce moment la il n est pas encore dans sockets actifs
}

void GameServer::sendMapSeedToClient(int socket_fd) {
    send_data(socket_fd, (char *) &mapSeed, sizeof(unsigned int));
}

void GameServer::sendQuadrantToClient(int socket_fd, int quadrant) {
    send_data(socket_fd, (char *) &quadrant, sizeof(int));
}


void GameServer::sendGameStateToPlayer(PlayerConnection &connection) {
    sendGameStateToPlayer(connection.getSocketFd());
}

void GameServer::sendGameStateToPlayer(int socket_fd) {
    // TODO: une autre approche serait de passer une reference de string vers
    // serializeGameState, dans lequel on ferait append. À considerer
    const std::string *serialized_game_state = gameEngine->serializeGameState();
    send_message(socket_fd, (*serialized_game_state).c_str());
    delete serialized_game_state;
}

void GameServer::removeClosedSocketFromSocketLists(int fd) {
    std::vector<PlayerConnection>::iterator iter;
    for (iter = playerConnections.begin(); iter != playerConnections.end(); iter++) {
        if ((*iter).getSocketFd() == fd) {
            playerConnections.erase(iter);
            return;
        }
    }

    for (auto iter2 = supportersSockets.begin(); iter2 != supportersSockets.end(); iter2++) {
        if ((*iter2) == fd) {
            supportersSockets.erase(iter2);
            return;
        }
    }

}

void GameServer::attemptSendMessageToClientSocket(int fd, const char *message) {
    if (socketIsActive(fd)) {
        int error_code = send_message(fd, message);
        if (error_code == -1) {
            removeClosedSocketFromSocketLists(fd);
        }
    }
}

bool GameServer::socketIsActive(int fd) {
    // TODO: pas efficace
    for (PlayerConnection &playerConnection: playerConnections) {
        if (playerConnection.getSocketFd() == fd) {
            return true;
        }
    }

    for (int socket: supportersSockets) {
        if (socket == fd) {
            return true;
        }
    }

    return false;
}

std::vector<PlayerConnection> &GameServer::getPlayerConnections() {
    return playerConnections;
}








