#include "GameServer.hpp"
#include "../client/GameManager.hpp"
#include "../common/AttackTower.hpp"

const bool DEBUG = false;

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections, std::string _mode) :
Server(port), playerConnections(playerConnections), mode(_mode) {

    if (!DEBUG){
        for (int i = 0; i < 4; i++) {
            client_sockets[i] = playerConnections[i].getSocket_fd();
        }
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



void GameServer::processClientCommands() {
    char message_buffer[BUFFER_SIZE];

    Timer timer;
    timer.start();
    int numSecondsElapsed = timer.elapsedTimeInSeconds();
    while (numSecondsElapsed < NUM_SECONDS_TO_PLACE_TOWER) {
        std::cout << "just before select" << std::endl;

        int timeLeft = NUM_SECONDS_TO_PLACE_TOWER - numSecondsElapsed;
        int client_index = get_readable_socket_index_with_timeout(client_sockets, 4, timeLeft);
        std::cout << "client selected: "<< client_index << std::endl;
        if (client_index < 0 || client_index > 4) return;

        int client_socket_fd = client_sockets[client_index];
        std::cout << "Client socket in server: " << client_socket_fd << std::endl;
        get_and_process_command(client_socket_fd, message_buffer);

        numSecondsElapsed = timer.elapsedTimeInSeconds();
    }
}

void GameServer::get_and_process_command(int client_socket_fd, char *buffer) {
//    int timeout = NUM_SECONDS_TO_PLACE_TOWER - timer.elapsedTimeInSeconds();
//    receive_message_with_timeout(client_socket_fd, buffer, 5);
    receive_message(client_socket_fd, buffer);
    std::cout << "Received command: " << buffer;
    std::string command_type = get_command_type(buffer);

    if (command_type == PLACE_TOWER_COMMAND_STRING) {
        TowerCommand command;
        command.parse(buffer);
        addTowerInGameState(command);
    }

    else if (command_type == DELETE_TOWER_COMMAND_STRING) {
        TowerCommand command;
        command.parse(buffer);
        deleteTowerInGameState(command);
    }

    else if (command_type == UPGRADE_TOWER_COMMAND_STRING) {
        TowerCommand command;
        command.parse(buffer);
        upgradeTowerInGameState(command);
    }

}

void GameServer::addTowerInGameState(TowerCommand &command) {
    AbstractTower * tower;
    int quadrant = command.getPlayerQuadrant();
    if (command.getTowerType() == ATTACK_TOWER_STR){
        AttackTower * attackTower = new AttackTower(command.getPosition());
        tower = attackTower;
    }
    else {
        // TODO: par défaut je mets une attacktower mais il faudra autre chose
        AttackTower * attackTower = new AttackTower(command.getPosition());
        tower = attackTower;
    }
    // TODO: completer si plus tard on utilise la SlowTower
    //else if (command.getTowerType() == SLOW_TOWER){
      //  *tower = SlowTower
    //}
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


void GameServer::runWave() {
    Timer timer;
    timer.start();
    gameEngine->createWaves();
    bool isWaveFinished = false;
    while (!isWaveFinished) {
        while (!isWaveFinished && timer.elapsedTimeInMiliseconds() < INTERVAL_BETWEEN_SENDS_IN_MS) {
            isWaveFinished = gameEngine->update();
            // TODO: mettre peut etre un sleep ici? on ne va pas faire des tonnes de updates de toute facon
            usleep(100); // C'est en microsecondes
            // car si gameEngine voit que pas assez de temps s'est ecoulé depuis le tick precedent,
            // il ne fait rien
        }

        if (DEBUG){
            gameEngine->showMap();
            // TODO: updateMap()
        } else {
            sendGameStateToPlayers();
        }
        timer.reset();
    }
}


void GameServer::run() {
    startSpectatorThread();
    runGame();
    stopSpectatorThread();
}

void GameServer::startSpectatorThread() {
    pthread_create(&spectatorJoinThread, NULL, &GameServer::staticJoinSpectatorThread, this);
}

void GameServer::runGame() {
    start_socket_listen();
    sleep(3); // TODO: find better way to avoid network race conditions...
    unsigned int mapSeed = (unsigned int) time(0);
    gameEngine = new GameEngine(mapSeed, mode);

    std::cout << "Le port du server est: " << port << std::endl;

    // Creer les playerState
    createPlayerStates();

    if (!DEBUG){
        setupGameForPlayers();
    }

    std::cout << "gameEngine->isGameFinished() = " << gameEngine->isGameFinished() << std::endl;
    while (!gameEngine->isGameFinished()) {
        if (!DEBUG){

            gameEngine->getTimerSinceGameStart().pause(); // peut etre faire ca juste en mode contre la montre
            sendTowerPhase();
            processClientCommands();
            gameEngine->getTimerSinceGameStart().resume(); // peut etre faire ca juste en mode contre la montre
            sendWavePhase();
        }
        runWave();
    }

    gameEngine->declareWinner();
    updatePlayerStatsOnAccountServer();
    delete gameEngine;


    //handleEndOfGame();
}

void GameServer::createPlayerStates() const {
    if (gameEngine->getGameState().getMode() == TEAM_MODE) {
        gameEngine->addPlayerState(playerConnections[0].getPlayer_id(), playerConnections[0].getUsername(), 1);
        gameEngine->addPlayerState(playerConnections[1].getPlayer_id(), playerConnections[0].getUsername(), 1);
        gameEngine->addPlayerState(playerConnections[2].getPlayer_id(), playerConnections[0].getUsername(), 2);
        gameEngine->addPlayerState(playerConnections[3].getPlayer_id(), playerConnections[0].getUsername(), 2);
    } else {
        for (int i = 0; i < 4; ++i) {
            gameEngine->addPlayerState(playerConnections[i].getPlayer_id(), playerConnections[0].getUsername());
        }
    }

}

void GameServer::sendTowerPhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocket_fd();
        send_message(socketFd, "t");
    }

    for (int socketFd: supportersSockets) {
        send_message(socketFd, "t");
    }
}

void GameServer::sendWavePhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocket_fd();
        send_message(socketFd, "w");
    }

    for (int socketFd: supportersSockets) {
        send_message(socketFd, "w");
    }
}




/*void GameServer::sendEndToPlayer(PlayerConnection &connection) {
    send_message(connection.getSocket_fd(), END_OF_GAME); //send "end" to client
}

void GameServer::sendWinnerToPlayer(PlayerConnection &connection) {
    int winner_id = gameEngine.getGameState().getWinnerClassic();
    send_message(connection.getSocket_fd(), std::to_string(winner_id).c_str());
}


void GameServer::handleEndOfGame() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendEndToPlayer(playerConnections[i]);
        sendWinnerToPlayer(playerConnections[i]);
    }
}
*/



int GameServer::connectToAccountServer() {
    return init_connection_to_server((char*) "127.0.0.1", 5555); //Faudrait mettre des constantes :)

}

void GameServer::updatePlayerStatsOnAccountServer() {
    int account_server_socket = connectToAccountServer();
    int p_id, pnj_killed;
    bool is_winner;

    send_message(account_server_socket, "Update;");

    for (PlayerState& ps : gameEngine->getGameState().getPlayerStates()){
        p_id = ps.getPlayer_id();
        pnj_killed = ps.getPnjKilled();
        is_winner = ps.getIsWinner();

        std::string message = "Update," + std::to_string(p_id)+ "," + std::to_string(pnj_killed) + "," +
                bool_to_string(is_winner) + ";";

        send_message(account_server_socket, message.c_str());
    }


}

void GameServer::stopSpectatorThread() {
    pthread_cancel(spectatorJoinThread);
}

static void *GameServer::staticJoinSpectatorThread(void * self) {
    static_cast<GameServer*>(self)->getAndProcessSpectatorJoinCommand();
    return nullptr;
}

void GameServer::getAndProcessSpectatorJoinCommand() {
    while (1) {
        int client_socket_fd = accept_connection();

        char command_buffer[BUFFER_SIZE];
        receive_message(socket_fd, command_buffer);

        /* Structure of command: "SUPPORT_PLAYER,bob;" */
        Command command;
        command.parse(command_buffer);

        if (command.getAction() == SUPPORT_PLAYER_STRING) {
            std::string username = command.getNextToken();
            PlayerState& playerState = getPlayerStateWithUsername(username);
            playerState.setIsSupported(true);

            supportersSockets.push_back(client_socket_fd);
            setupGameForPlayer(client_socket_fd, getQuadrantForPlayer(username));
        }
    }
}


std::string GameServer::getMode() {
    return mode;
}

PlayerState &GameServer::getPlayerStateWithUsername(std::string username) {
    for(PlayerState& playerState: gameEngine->getGameState().getPlayerStates()){
        if (playerState.getUsername() == username) {
            return playerState;
        }
    }
}

int GameServer::getQuadrantForPlayer(std::string username){
    int quadrant = 0;
    for (PlayerConnection &playerConnection: playerConnections) {
        if (playerConnection.getUsername() == username) {
            return quadrant;
        }
        quadrant++;
    }
}

std::string GameServer::getAllPlayers() {
    std::string res ="";
    int count = 1;

    for (auto& pc : playerConnections){

        res += pc.getUsername();
        res += count == playerConnections.size() ? ";" : ",";
        count++;
    }
    return res;
}

void GameServer::setupGameForPlayers() {
    unsigned int quadrant = 0;
    for (PlayerConnection& playerConnection: playerConnections) {
        int player_socket_fd = playerConnection.getSocket_fd();
        setupGameForPlayer(player_socket_fd, quadrant);
        quadrant++;
    }
}

void GameServer::setupGameForPlayer(int player_socket_fd, int quadrant){
    sendSetupGameStringToClient(player_socket_fd);
    sendMapSeedToClient(player_socket_fd);
    sendQuadrantToClient(player_socket_fd, quadrant);
    sendGameStateToPlayer(player_socket_fd);
}

void GameServer::sendSetupGameStringToClient(int socket_fd) {
    send_message(socket_fd, SETUP_GAME);
}

void GameServer::sendMapSeedToClient(int socket_fd) {
    send_data(socket_fd, (char *) &mapSeed, sizeof(unsigned int));
}

void GameServer::sendQuadrantToClient(int socket_fd, int quadrant) {
    send_data(socket_fd, (char *) &quadrant, sizeof(int));
}

void GameServer::sendInitialGameState() {
    sendGameStateToPlayers();
}

void GameServer::sendGameStateToPlayer(PlayerConnection &connection) {
    sendGameStateToPlayer(connection.getSocket_fd());
}

void GameServer::sendGameStateToPlayer(int socket_fd) {
    // TODO: une autre approche serait de passer une reference de string vers
    // serializeGameState, dans lequel on ferait append. À considerer
    const std::string * serialized_game_state = gameEngine->serializeGameState();
    send_message(socket_fd, (*serialized_game_state).c_str());
    delete serialized_game_state;
}