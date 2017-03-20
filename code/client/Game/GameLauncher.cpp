#include <assert.h>
#include "GameLauncher.hpp"
#include "GameManager.hpp"

GameLauncher::GameLauncher(int port, App* app, std::string _mode) :
        NetworkedManager(port, app), mode(_mode) {}

void GameLauncher::run() {
    sendJoinRequest();
}

void GameLauncher::sendJoinRequest() {

    /* Partie 1: envoyer demanded pour rejoindre le jeu */
    char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

    std::string message = mode + "," + std::to_string(master_app->getId()) +
            "," + master_app->getUsername() + ";";
    send_message(server_socket, message.c_str());
    std::cout << "In Queue..." << std::endl;


    /* Recevoir reponse du server */
    receive_message(server_socket, server_response);
    assert(strcmp(server_response, GAME_STARTING_STRING.c_str()) == 0);

    if (strcmp(server_response, GAME_STARTING_STRING) == 0) {
        /*Recevoir port du GamesServer auquel se connecter */
        int game_port;
        receive_data(server_socket, &game_port, sizeof(int));


        if (isConsole) { launchGame(); }
    }

}

void GameLauncher::leaveQueue() {
    std::string message = LEAVE_QUEUE_REQUEST + ',' + mode + ';';
    std::cout << message << std::endl;
    send_message(server_socket, message.c_str());

}

void GameLauncher::launchGame() {
    std::cout << "Game start" << std::endl;

    GameManager* manager = new GameManager(server_socket, master_app);
    master_app->transition(manager);

}
