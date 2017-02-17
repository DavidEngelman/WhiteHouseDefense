#include "GameLauncher.hpp"
#include "../common/Strings.hpp"

GameLauncher::GameLauncher(int port, char *address) : NetworkedManager(port, address) {
};

void GameLauncher::sendJoinRequest(std::string mode) {
    int player_id = 0; // TODO: get real player ID
    char server_response[20];

    std::string message = mode + "," + std::to_string(player_id) + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);

    if (strcmp(server_response, GAME_STARTING_STRING) == 0) {
        // Start game
    } else {
        std::cout << "Invalid response from server." << std::endl;
    }
}
