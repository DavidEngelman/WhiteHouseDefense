
#include "GameServer.hpp"
#include "Timer.h"

void GameServer::sendGameStateToPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendGameStateToPlayer(playerConnections[i]);
    }
}

void GameServer::sendGameStateToPlayer(PlayerConnection &connection) {
    const std::string &serialized_game_state = gameState.serialize();
    send_message(connection.socket_fd, serialized_game_state.c_str());
}

void GameServer::processClientCommands() {
    char message_buffer[BUFFER_SIZE];

    Timer timer;
    timer.start();
    // TODO: choisir le temps d'attente et le mettre comme une constante
    while (timer.elapsedTimeInSeconds() < 60) {
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
//    gameState.add_tower(command.getPosition());
}

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections) :
        Server(port), playerConnections(playerConnections.data()) {}

void GameServer::runWave() {
    Timer timer;
    timer.start();
    while (!gameState.isWaveFinished() && !gameState.isFinished()) {
        // TODO: choisir une meilleure valeur et la mettre comme constant
        while (!timer.elapsedTimeInMiliseconds() < 1000) {
            // gameState.update(); // ou peut etre gameState.update(timeEllapsed)?
        }

        sendGameStateToPlayers();
        timer.reset();
    }
}


void GameServer::run() {
    while (!gameState.isFinished()) {
        processClientCommands();
        runWave();
    }
}