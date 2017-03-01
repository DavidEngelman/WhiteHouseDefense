#include "SpectatorManager.hpp"


SpectatorManager::SpectatorManager(int port, char *adress, App *my_app) : NetworkedManager(port, adress, my_app) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, GAME_IN_PROGRESS_REQUEST);
    receive_message(server_socket, buffer); //receive all the games in progress
}

