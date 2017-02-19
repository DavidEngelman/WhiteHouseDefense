#include "GameLauncher.hpp"
#include "../common/Strings.hpp"

GameLauncher::GameLauncher(int port, char *address, int id) : NetworkedManager(port, address), player_id(id) {
    sendJoinRequest(CLASSIC_MODE);
};

void GameLauncher::sendJoinRequest(std::string mode) {
    char server_response[20];

    std::string message = mode + "," + std::to_string(player_id) + ";";
    send_message(server_socket, message.c_str());
    std::cout << "In Queue..." << std::endl;
    receive_message(server_socket, server_response);

    std::cout << server_response << std::endl;

    while(strcmp(server_response, GAME_STARTING_STRING) != 0) {/*wait*/}

    std::cout << "Game start" << std::endl;

}