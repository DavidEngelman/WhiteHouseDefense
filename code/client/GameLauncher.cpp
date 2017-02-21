#include <assert.h>
#include "GameLauncher.hpp"
#include "../common/Strings.hpp"
#include "GameManager.hpp"

GameLauncher::GameLauncher(int port, char *address, int id) : NetworkedManager(port, address), player_id(id) {
    sendJoinRequest(CLASSIC_MODE);
};

void GameLauncher::sendJoinRequest(std::string mode) {

    /* Partie 1: envoyer demanded pour rejoindre le jeu */
    char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

    std::string message = mode + "," + std::to_string(player_id) + ";";
    send_message(server_socket, message.c_str());
    std::cout << "In Queue... avec le socket " << server_socket << std::endl;


    /* Recevoir reponse du server */
    receive_message(server_socket, server_response);
    assert(strcmp(server_response, GAME_STARTING_STRING) == 0);

    std::cout << "Game start" << std::endl;
    GameManager gameManager = GameManager();
}