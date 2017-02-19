
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

// pq on exectuerait pas 2 threads dans la boucle while !waveHasFinished.
// 1 qui fait des gamestate.update() tous les x temps
// et 1 qui fait des sendGameStateToPlayers() tous les x temps ?
// on peut faire genre une fct comme ca :
/*
void GameServer::doUpdate(){ //fct pour le 1er thread
    while(1){
        gameState.update;
    }
}

void GameServer::doSending() { //fct pour le 2eme thread
    while(1){
        sleep(x); //temps à déterminer
        sendGameStateToPlayers();
    }

}
*/

/*
 * L'idée des threads est bonne à mon avis, mais je vois pas trop le besoin pour ce cas ci
 * On pourrait faire tout simplement
 * void runWave(){
     * start = time()
     * while (1) {
     *     current = time()
     *     while (current - start < X) {
     *          gameState.update()
     *          current = time()
     *     }
     *     sendGameStateToPlayers()
     *     start = time()
     * }
 * }
 *
 * L'avantage que je vois est que on ferait des gameUpdate un peu plus regulierement, mais je ne sais pas
 * si c'est vraiment un probleme ça.
 *
 * Je crois que ça va surtout être utile quand on le client pourra placer des tours pendant une vague.
 *
 * Par exemple on pourrait faire tourner en parallèle sur 2 threads les
 * fonctions runGame (dans mon exemple) et processClientCommands, avec un mutex pour assurer la coherence.
 *
 *
 *
 */

void GameServer::run() {
    while (!gameState.isFinished()) {
        processClientCommands();
        runWave();
    }
}