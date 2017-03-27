#include <csignal>
#include <iostream>
#include "GameServer.hpp"
#include "../../common/Tower/GunTower.hpp"
#include "../../common/Tower/SniperTower.hpp"
#include "../../common/Tower/ShockTower.hpp"
#include "../../common/Tower/MissileTower.hpp"

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode) :
        Server(port), playerConnections(playerConnections), mode(_mode) {
    srand((unsigned) time(0));
    mapSeed = (unsigned int) rand() % NB_OF_MAPS;
    std::ifstream Fichier("../../Utiles/Dico.txt");
    if(Fichier)
    {
        std::string ligne;
        dico = " ";
        while(getline(Fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            dico += ligne + " ";
        }
    }
    else
    {
        std::cout << "ERROR: Impossible to open the file" << std::endl;
    }

}

void GameServer::run() {
    startSpectatorThread();
    startInputThread();
    runGame();
    handleEndOfGame();
}

void GameServer::handleEndOfGame() {
    stopSpectatorThread();
    stopSpectatorCommandThreads();
    stopInputThread();
    updatePlayerStatsOnAccountServer();
    sendFinishedToMatchmaker();
    delete gameEngine;
}

void GameServer::runGame() {

    start_socket_listen();
    // TODO: find better way to avoid network race conditions...
    // Ideally, we'd only launch the server when the matchmaker has received the 4 confirmations from
    // the players, but that's quite a bit of work and little reward
    sleep(2);
    gameEngine = new GameEngine(mapSeed, mode);

    // Creer les playerState
    createPlayerStates();

    setupGameForPlayers();

    while (!gameEngine->isGameFinished() && !playerConnections.empty()) {
        gameEngine->getTimerSinceGameStart().pause(); // peut etre faire ca juste en mode contre la montre
        sendTowerPhase();
        Timer timer;
        timer.start();
        while (timer.elapsedTimeInSeconds() < NUM_SECONDS_TO_PLACE_TOWER) {
            usleep((__useconds_t) (INTERVAL_BETWEEN_TOWER_PHASE_SENDS_IN_MS * 1000));
            sendGameStateToPlayers();
        }
        gameEngine->getTimerSinceGameStart().resume(); // peut etre faire ca juste en mode contre la montre
        sendWavePhase();
        runWave();
    }
}

/*
 * GAME EVOLUTION AND UPDATE; COMMUNICATION WITH CLIENT
 */

void GameServer::runWave() {
    Timer timer;
    timer.start();
    gameEngine->createWaves();
    bool isWaveFinished = false;
    while (!isWaveFinished && !playerConnections.empty()) {
        while (!isWaveFinished && timer.elapsedTimeInMiliseconds() < INTERVAL_BETWEEN_SENDS_IN_MS) {
            isWaveFinished = gameEngine->update();
        }
        sendGameStateToPlayers();
        timer.reset();
    }
}


void GameServer::sendGameStateToPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendGameStateToPlayer(playerConnections[i]);
    }

    for (SupporterConnection &supporterConnection: supporterConnections) {
        sendGameStateToPlayer(supporterConnection.getSupporterSocket());
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

void *GameServer::staticInputThread(void *self) {
    static_cast<GameServer *>(self)->getAndProcessPlayerInput();
    return nullptr;
}

void GameServer::getAndProcessPlayerInput() {
    char messageBuffer[BUFFER_SIZE];
    while (!playerConnections.empty()) {
        // TODO: the 10000 is absurdly high, not sure it's a good idea
        int clientSocketFd = getReadableReadableSocket(10000);
        std::cout << "after getReadableReadableSocket" << std::endl;
        getAndProcessUserInput(clientSocketFd, messageBuffer);
    }
}

void GameServer::getAndProcessUserInput(int clientSocketFd, char *buffer) {
    std::cout << "Just before receive from: " << clientSocketFd << std::endl;

    if (receive_message(clientSocketFd, buffer) > 0) {
        std::cout << "Received message from: " << clientSocketFd << std::endl;
        std::string command_type = get_command_type(buffer);
        std::cout << command_type << std::endl;
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
        } else if (command_type == SEND_MESSAGE_STRING) {
            Command command;
            command.parse(buffer);
            int messageLength = command.getNextInt();
            std::string userMessage = command.getTokenWithSize(messageLength);
            changeVulgarityToStar(userMessage);
            std::string senderUsername = command.getNextToken();

            if (!userMessage.empty() && userMessage[0] == '/') {
                processSpecialCommand(userMessage, senderUsername);
            } else {
                sendMessageToOtherPlayers(userMessage, senderUsername);
            }
        } else if (command_type == NUCLEAR_BOMB_COMMAND_STRING) {
            Command command;
            command.parse(buffer);
            int quadrant = command.getNextInt();
            gameEngine->killAllNPC(quadrant);
            sendNotification(quadrant, 0);
        } else if (command_type == FREEZE_PNJS_COMMAND_STRING) {
            Command command;
            command.parse(buffer);
            int quadrant = command.getNextInt();
            gameEngine->freezeWave(quadrant);
            sendNotification(quadrant, 1);
        } else if (command_type == AIR_STRIKE_COMMAND_STRING) {
            Command command;
            command.parse(buffer);
            int quadrant = command.getNextInt();
            int targetQuadrant = command.getNextInt();
            gameEngine->launchAirStrike(targetQuadrant);
            sendAirstrikeNotification(quadrant, targetQuadrant);
        } else if (command_type == HEAL_TEAM_COMMAND_STRING) {
            Command command;
            command.parse(buffer);
            int quadrant = command.getNextInt();
            gameEngine->healTeam(quadrant);

        }
    } else {
        removeClosedSocketFromSocketLists(clientSocketFd);
    }
}

void GameServer::sendMessageToOtherPlayers(std::string &userMessage, std::string &senderUsername) {
    std::string message = makeMessage(userMessage, senderUsername);
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        send_message(socketFd, message.c_str());
    }
}

void GameServer::sendAdPopUP(std::string &playerSupportedUserName) {
    std::string message = AD_POPUP;
    for (PlayerConnection &playerConnection : playerConnections) {
        if (playerConnection.getUsername() != playerSupportedUserName) {
            int socketFd = playerConnection.getSocketFd();
            send_message(socketFd, message.c_str());
            std::cout << "sent popUp" << std::endl;
        }
    }
}

void GameServer::sendNotification(int quadrant, int notificationID) {
    std::string &sender = gameEngine->getGameState().getPlayerStates()[quadrant].getUsername();
    std::string notification;
    if (notificationID == 0) {
        notification = sender + " launched a nuclear bomb";
    } else if (notificationID == 1) {
        notification = sender + " used the frozen spell";
    }
    std::string message = makeMessage(notification, "[SERVER] ");
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        send_message(socketFd, message.c_str());
    }

}

void GameServer::sendAirstrikeNotification(int quadrant, int targetQuadrant) {
    std::string &sender = gameEngine->getGameState().getPlayerStates()[quadrant].getUsername();
    std::string &target= gameEngine->getGameState().getPlayerStates()[targetQuadrant].getUsername();
    std::string notification;

    notification = sender + " launched an aistrike on " + target + "'s base";

    std::string message = makeMessage(notification, "[SERVER] ");
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        send_message(socketFd, message.c_str());
    }

}



std::string GameServer::makeMessage(const std::string &userMessage, const std::string &senderUsername) const {
    std::string message = RECEIVE_MESSAGE_STRING + ","
                          + std::to_string(userMessage.size()) + ","
                          + userMessage + ","
                          + senderUsername + ";";
    return message;
}

int GameServer::getReadableReadableSocket(int timeLeft) {
    // TODO: solution temporaire. C'est debile de creer des vecteurs à chaque appel
    std::vector<int> open_sockets;
    for (PlayerConnection &playerConnection: playerConnections) {
        open_sockets.push_back(playerConnection.getSocketFd());
    }
    std::cout << "just after for loop" << std::endl;

    int socketIndex = get_readable_socket_index_with_timeout(open_sockets.data(),
                                                             (int) open_sockets.size(), timeLeft);
    std::cout << "Readable socket: " << open_sockets[socketIndex] << std::endl;
    return open_sockets[socketIndex];
}

void GameServer::addTowerInGameState(TowerCommand &command) {
    AbstractTower *tower;
    if (command.getTowerType() == GUN_TOWER_STR) {
        tower = new GunTower(command.getPosition(), 1);
    } else if (command.getTowerType() == SNIPER_TOWER_STR) {
        tower = new SniperTower(command.getPosition(), 1);
    } else if (command.getTowerType() == SHOCK_TOWER_STR) {
        tower = new ShockTower(command.getPosition(), 1);
    } else {
        tower = new MissileTower(command.getPosition(), 1);
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

void GameServer::startSpectatorCommandThread(int _client_socket) {
    pthread_t spectatorReceiverThread;
    argsForSpectatorCommandThread *args = new argsForSpectatorCommandThread;
    args->gameServer = this;
    args->client_socket = _client_socket;
    pthread_create(&spectatorReceiverThread, NULL, staticProcessSpectatorCommandThread, (void*) args);
    spectatorReceiverThreads.push_back(spectatorReceiverThread);
}

void GameServer::stopSpectatorCommandThreads() {
    for (auto &thread : spectatorReceiverThreads) {
        pthread_cancel(thread);
    }
}

void *GameServer::staticProcessSpectatorCommandThread(void *arguments) {
    argsForSpectatorCommandThread args = *(argsForSpectatorCommandThread*)arguments;
    int supporterSocketFd = args.client_socket;
    GameServer* self = args.gameServer;
    self->getAndProcessSpectatorCommand(supporterSocketFd);

    delete (argsForSpectatorCommandThread*)arguments;
    return nullptr;
}

SupporterConnection GameServer::getSupporterConnection(int socket) {
    for (auto &connection : supporterConnections) {
        if (connection.getSupporterSocket() == socket) {
            return connection;
        }
    }
}

void GameServer::getAndProcessSpectatorJoinCommand() {
    while (!playerConnections.empty()) {
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
            SupporterConnection connection;
            connection.setSupporterSocket(client_socket_fd);
            connection.setPlayerSupported(username);

            supporterConnections.push_back(connection);
            startSpectatorCommandThread(client_socket_fd);
        }
    }
}

void GameServer::getAndProcessSpectatorCommand(int supporterSocketFd) {
    char buffer[BUFFER_SIZE];
    bool online = true;
    while (online) {
        if (receive_message(supporterSocketFd, buffer) > 0) {
            std::cout << "Received message from: " << supporterSocketFd << std::endl;
            std::string command_type = get_command_type(buffer);
            std::cout << command_type << std::endl;

            if (command_type == SEND_MESSAGE_STRING) {
                Command command;
                command.parse(buffer);
                int messageLength = command.getNextInt();
                std::string userMessage = command.getTokenWithSize(messageLength);
                std::string senderUsername = command.getNextToken();

                if (!userMessage.empty() && userMessage[0] == '/') {
                    processSpecialCommand(userMessage, senderUsername);
                } else {
                    sendMessageToOtherPlayers(userMessage, senderUsername);
                }
            } else if (command_type == AD_SPELL_COMMAND_STRING) {
                Command command;
                command.parse(buffer);
                std::string playerSupportedUserName = command.getNextToken();
                sendAdPopUP(playerSupportedUserName);
            }

        } else {
            SupporterConnection connection = getSupporterConnection(supporterSocketFd);

            PlayerState &playerState = getPlayerStateWithUsername(connection.getPlayerSupported());
            playerState.setIsSupported(false);
            removeClosedSocketFromSocketLists(supporterSocketFd);
            online = false;
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

/* Returns the number of the quadrant of the player with that username.
 * If there is no such player, returns -1 */
int GameServer::getQuadrantForPlayer(std::string username) {
    int quadrant = 0;
    for (PlayerConnection &playerConnection: playerConnections) {
        if (playerConnection.getUsername() == username) {
            return quadrant;
        }
        quadrant++;
    }
    return -1;
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

    for (SupporterConnection &supporterConnection : supporterConnections) {
        int socketFd = supporterConnection.getSupporterSocket();
        attemptSendMessageToClientSocket(socketFd, "t");
    }
}

void GameServer::sendWavePhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocketFd();
        attemptSendMessageToClientSocket(socketFd, "w");
    }

    for (SupporterConnection &supporterConnection : supporterConnections) {
        int socketFd = supporterConnection.getSupporterSocket();
        attemptSendMessageToClientSocket(socketFd, "t");
    }
}

int GameServer::connectToServer(int port) {
    return init_connection_to_server((char *) "127.0.0.1", port); //Faudrait mettre des constantes :)

}

void GameServer::sendFinishedToMatchmaker() {
    int matchmaker_server_socket = connectToServer(MATCHMAKER_SERVER_PORT);
    std::string message = "PopGame," + std::to_string(port) + ";";
    send_message(matchmaker_server_socket, message.c_str());
}

void GameServer::updatePlayerStatsOnAccountServer() {
    int account_server_socket = connectToServer(ACCOUNT_SERVER_PORT);
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
    send_message(socket_fd, SETUP_GAME.c_str());
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
    const std::string *serialized_game_state = gameEngine->serializeGameState();
    send_message(socket_fd, (*serialized_game_state).c_str());
    delete serialized_game_state;
}

void GameServer::removeClosedSocketFromSocketLists(int fd) {
    std::vector<PlayerConnection>::iterator iter;
    for (iter = playerConnections.begin(); iter != playerConnections.end(); iter++) {
        if ((*iter).getSocketFd() == fd) {
            playerConnections.erase(iter);
            // If there aren't players anymore, it stops the game
            if (playerConnections.empty()) {
                tellSupportersTheGameIsOver();
            }
            return;
        }
    }

    for (auto iter2 = supporterConnections.begin(); iter2 != supporterConnections.end(); iter2++) {
        if ((*iter2).getSupporterSocket() == fd) {
            supporterConnections.erase(iter2);
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

    for (SupporterConnection &supporterConnection: supporterConnections) {
        if (supporterConnection.getSupporterSocket()) {
            return true;
        }
    }

    return false;
}

std::vector<PlayerConnection> &GameServer::getPlayerConnections() {
    return playerConnections;
}

void GameServer::tellSupportersTheGameIsOver() {
    gameEngine->getGameState().setIsGameOver(true);
    for (SupporterConnection &supporterConnection : supporterConnections) {
        sendGameStateToPlayer(supporterConnection.getSupporterSocket());
    }
}

void GameServer::processSpecialCommand(std::string &userMessage, std::string &senderUsername) {
    std::string MESSAGE_COMMAND = "/msg";
    std::string TEAM_COMMAND = "/team";
    Message message(' ');
    message.setData((char *) userMessage.c_str());

    const std::string &firstToken = message.getNextToken();
    if (firstToken == "/msg") {
        const std::string &receiverUsername = message.getNextToken();
        int receiverQuadrant = getQuadrantForPlayer(receiverUsername);
        if (receiverQuadrant != -1) { // There is a player with that username
            int senderQuadrant = getQuadrantForPlayer(senderUsername);
            const std::string &finalMessage = makeMessage(message.getRemainingContent(), "[PRIVATE] " + senderUsername);

            // Send to myself and to team mate
            send_message(playerConnections[senderQuadrant].getSocketFd(), finalMessage.c_str());
            send_message(playerConnections[receiverQuadrant].getSocketFd(), finalMessage.c_str());
        } else {
            sendMessageToOtherPlayers(userMessage, senderUsername);
        }
    } else if (firstToken == "/team" && mode == TEAM_MODE) {
        int senderQuadrant = getQuadrantForPlayer(senderUsername);
        int teamMateQuadrants[4] = {1, 0, 3, 2};
        int teamMateQuadrant = teamMateQuadrants[senderQuadrant];
        const std::string &finalMessage = makeMessage(message.getRemainingContent(), "[TEAM] " + senderUsername);

        // Send to myself and to team mate
        send_message(playerConnections[senderQuadrant].getSocketFd(), finalMessage.c_str());
        send_message(playerConnections[teamMateQuadrant].getSocketFd(), finalMessage.c_str());
    } else {
        sendMessageToOtherPlayers(userMessage, senderUsername);
    }
}

void GameServer::changeVulgarityToStar(std::string &userMessage) {
    int count = 0;
    std::string mot;

    for (char& c : userMessage) {
        if (c == ' ') {
            findAndChangeToStarVulgarities(mot, count, userMessage);
            count += mot.size() + 1;
            mot = "";
        }

        else {
            mot += c;
        }
    }
    findAndChangeToStarVulgarities(mot, count, userMessage);
}
void GameServer::findAndChangeToStarVulgarities(std::string mot, int count, std::string &userMessage){
    unsigned long taille = mot.size();
    for(int i = 0; i<taille; i++){
        mot[i] = (char) tolower(mot[i]);
    }
    mot = ' ' + mot +' ';
    if (dico.find(mot) != std::string::npos) {
        for (int i = 0; i < taille; i++) {
            userMessage[count + i] = '*';
        }
    }
}