
#include "GameServer.hpp"

GameServer::GameServer(int port) : Server(port) {}

void GameServer::sendGameStateToPlayer() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        sendGameStateToPlayer(playerConnections[i]);
    }
}

void GameServer::sendGameStateToPlayer(PlayerConnection &connection) {
    const std::string &serialized_game_state = gameState.serialize();
    send_message(connection.socket_fd, serialized_game_state.c_str());
}
