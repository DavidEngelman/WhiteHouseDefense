#include "SpectatorManager.hpp"


SpectatorManager::SpectatorManager(int port, char* address, int id, std::string username, App* master_app) :
        NetworkedManager(port, address, master_app) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, GAME_IN_PROGRESS_REQUEST);
    receive_message(server_socket, buffer); //receive all the games in progress

    std::string pretty_string = parse_message_from_server(std::string(buffer));

    spectatorUI.displaySpectatorUI();
}

void SpectatorManager::run() {}

std::string SpectatorManager::parse_message_from_server(std::string message){
    //5555,classic,bob,bib,bab;5557,timeMode,bob,bib,bab;



}