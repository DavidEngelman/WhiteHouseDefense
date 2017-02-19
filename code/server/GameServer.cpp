
#include "GameServer.hpp"

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

    // TODO: cette condition devra être modifiée. Il faut que ça s'arrete au bout de X secondes,
    // c'est à dire la phase où les clients peuvent placer les tours.
    time_t end_wait;
    time_t current = time(NULL);
    time_t time_to_wait = 60; //60 secondes pour placer ses tours
    end_wait = current + time_to_wait;

    while (current < end_wait){
        int client_socket_fd = accept_connection();
        get_and_process_command(client_socket_fd, message_buffer);
        current = time(NULL);
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

GameServer::GameServer(int port, std::vector<PlayerConnection> &playerConnections):
        Server(port), playerConnections(playerConnections.data())
{}

void GameServer::runWave() {

    // TODO: il faut controller le rythme auquel on envoie des informations
    // On sait peut etre faire un update du jeu 10000x par seconde, mais on veut surement pas
    // envoyer 10000x par seconde des données au client
    // Il faudra donc un mecanisme pour controler le temps

    // TODO: il faut aussi faire update de cette condition, pour que ça s'arrete quand la vague est finie.
    bool waveHasFinished = false;
    while (!waveHasFinished){
        bool shouldSendData = false;
        while (!shouldSendData){
            // gameState.update(); // ou peut etre gameState.update(timeEllapsed)?
            // TODO: Il faudra voir comment est-ce qu'on fait evoluer le jeu en fonction du temps
            shouldSendData = false; // TODO: update
        }

        sendGameStateToPlayers();

        // En attendant
        shouldSendData = false;
        waveHasFinished = false;
    }
}

void GameServer::run() {
    bool gameHasEnded = false;
    while (!gameHasEnded){
        processClientCommands();
        runWave();

        // TODO: faudra trouver un moyen de voir quand le jeu est fini
        gameHasEnded = false;
    }
}

bool GameServer::isFinishedClassic() {
    return gameState.isOnlyOneAlive();
}

bool GameServer::isFinishedCoop() {
    //TODO
}

bool GameServer::isFinishedVsTime() {
    //TODO
}