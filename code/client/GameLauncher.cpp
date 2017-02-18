#include "GameLauncher.hpp"
#include "../common/Strings.hpp"

GameLauncher::GameLauncher(int port, char *address, int id) : NetworkedManager(port, address), player_id(id) {
};

void GameLauncher::sendJoinRequest(std::string mode) {
    char server_response[20];

    std::string message = mode + "," + std::to_string(player_id) + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);

    if (strcmp(server_response, GAME_STARTING_STRING) == 0) {
        std::cout << "Game start !";
    } else {
        std::cout << "Invalid response from server." << std::endl;
    }
}
