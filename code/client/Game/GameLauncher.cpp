#include "GameLauncher.hpp"
#include "GameManager.hpp"

GameLauncher::GameLauncher(int port, App* app, std::string _mode) :
        NetworkedManager(port, app), mode(_mode) {}

void GameLauncher::sendJoinRequest() {
    /* Partie 1: envoyer demanded pour rejoindre le jeu */
    char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

    std::string message = mode + "," + std::to_string(master_app->getId()) +
                          "," + master_app->getUsername() + ";";
    send_message(server_socket, message.c_str());
    std::cout << "In Queue..." << std::endl;


    /* Recevoir reponse du server */
    receive_message(server_socket, server_response);

    /*Recevoir port du GamesServer auquel se connecter */

    // TODO: pour l'instant on recoit le port du gameServer, mais ca ne sert a rien pour l'instant
    // parce qu'on communique au GameServer via le socket qu'on avait avec la Matchmaker
    int game_port;
    receive_data(server_socket, &game_port, sizeof(int));

    // Envoyer au matchmaker un string pour lui dire de ne plus faire receive sur le socket,
    // car c'est maintenant le GameServer qui communique via ce socket
    std::string matchmakerMessage = GAME_STARTED_STRING + ";";
    send_message(server_socket, matchmakerMessage.c_str());

    std::cout << "Game start" << std::endl;
    GameManager* manager = new GameManager(server_socket, master_app);
    master_app->transition(manager);
}

void GameLauncher::run() {
    sendJoinRequest();
}