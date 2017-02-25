#include "GameServer.hpp"
#include "../client/GameManager.hpp"
#include "../common/AttackTower.hpp"

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections) :
Server(port), playerConnections(playerConnections) {}

void GameServer::sendGameStateToPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendGameStateToPlayer(playerConnections[i]);
    }
}

void GameServer::sendGameStateToPlayer(PlayerConnection &connection) {
    // TODO: une autre approche serait de passer une reference de string vers
    // serializeGameState, dans lequel on ferait append. À considerer
    const std::string * serialized_game_state = gameEngine.serializeGameState();
    send_message(connection.getSocket_fd(), (*serialized_game_state).c_str());
    delete serialized_game_state;
}

void GameServer::processClientCommands() {
    char message_buffer[BUFFER_SIZE];

    Timer timer;
    timer.start();
    while (timer.elapsedTimeInSeconds() < NUM_SECONDS_TO_PLACE_TOWER) {
        // TODO: faire un select sur les sockets des joueurs dans PlayerConnection.
        int client_socket_fd = accept_connection();
        get_and_process_command(client_socket_fd, message_buffer);
    }
}

void GameServer::get_and_process_command(int client_socket_fd, char *buffer) {
    receive_message(client_socket_fd, buffer);
    std::string command_type = get_command_type(buffer);

    if (command_type == PLACE_TOWER_COMMAND_STRING) {
        PlaceTowerCommand command;
        command.parse(buffer);
        addTowerInGameState(command);
    }

}

void GameServer::addTowerInGameState(PlaceTowerCommand &command) {
    AbstractTower * tower;
    int quadrant = command.getPlayerQuadrant();
    if (command.getTowerType() == ATTACK_TOWER_STR){
        *tower = AttackTower(command.getPosition());
    }
    // TODO: completer si plus tard on utilise la SlowTower
    //else if (command.getTowerType() == SLOW_TOWER){
      //  *tower = SlowTower
    //}
    gameEngine.addTower(*tower, quadrant);
}

void GameServer::runWave() {
    Timer timer;
    timer.start();

    bool isWaveFinished = false;
    while (!isWaveFinished) {
        while (!isWaveFinished && !timer.elapsedTimeInMiliseconds() < INTERVAL_BETWEEN_SENDS_IN_MS) {
            isWaveFinished = gameEngine.update();
            // TODO: mettre peut etre un sleep ici? on ne va pas faire des tonnes de updates de toute facon
            // car si gameEngine voit que pas assez de temps s'est ecoulé depuis le tick precedent,
            // il ne fait rien
        }

        sendGameStateToPlayers();
        timer.reset();
    }
}


void GameServer::run() {
    setupGame();

    while (!gameEngine.isGameFinished()) {
        sendTowerPhase();
        processClientCommands();
        sendWavePhase();
        runWave();
    }

    //handleEndOfGame();
}

void GameServer::sendTowerPhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocket_fd();
        send_message(socketFd, PLACING_TOWER);

    }
}

void GameServer::sendWavePhase() {
    for (PlayerConnection &playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocket_fd();
        send_message(socketFd, WAVE);
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
void GameServer::setupGame() {
    unsigned int mapSeed = gameEngine.getGameState().getMapSeed();
    std::string message = "seed";
    for (PlayerConnection& playerConnection : playerConnections) {
        int socketFd = playerConnection.getSocket_fd();
        send_message(socketFd, message.c_str());
        send_data(socketFd, (char *) &mapSeed, sizeof(unsigned int));
    }
}
