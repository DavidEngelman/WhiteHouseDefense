#include <assert.h>
#include "GameLauncher.hpp"
#include "../common/Strings.hpp"
#include "GameManager.hpp"

GameLauncher::GameLauncher(int port, char *address, int id, std::string name, App* app, std::string _mode) :
        NetworkedManager(port, address, app), player_id(id), player_name(name), mode(_mode) {}

void GameLauncher::sendJoinRequest() {

    /* Partie 1: envoyer demanded pour rejoindre le jeu */
    char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

    std::string message = mode + "," + std::to_string(player_id) + "," + player_name + ";";
    send_message(server_socket, message.c_str());
    std::cout << "In Queue... avec le socket " << server_socket << std::endl;


    /* Recevoir reponse du server */
    receive_message(server_socket, server_response);
    assert(strcmp(server_response, GAME_STARTING_STRING) == 0);

    /*Recevoir port du GamesServer auquel se connecter */
    int game_port;
    receive_data(server_socket, &game_port, sizeof(int));

    std::cout << "Game start" << std::endl;
    GameManager* manager = new GameManager(server_ip_address, game_port, server_socket, player_id, player_name, master_app);
    master_app->transition(manager);
}

void GameLauncher::run() {
    sendJoinRequest();
}