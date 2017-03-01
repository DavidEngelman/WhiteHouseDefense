#include "SpectatorManager.hpp"

//"5557,classic,bibi,baba,bobo,bubu;5558,classic,lala,lili,lolo,lele;"

SpectatorManager::SpectatorManager(int port, char* address, int id, std::string username, App* master_app) :
        NetworkedManager(port, address, master_app) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    //receive_message(server_socket, buffer); //receive all the games in progress

    parse_message_from_server(std::string(buffer));

    if (allGames.size() == 0){
        spectatorUI.displaySorryMessage();

    }
    else{
        spectatorUI.displaySpectatorUI(allGames);
        int gameSelected = spectatorUI.inputSpectatorUI(allGames.size());
    }

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();
}

void SpectatorManager::parse_message_from_server(const std::string &message) {
    int i = 0;
    while (i < message.size()) {
        i = createGameInfo(message, i);
    }
}

int SpectatorManager::createGameInfo(const std::string& message, int& i) {

    std::string str_port, str_mode, str_players;
    while (message[i] != ',') {
        str_port += message[i];
        i++;
    }
    i++;
    while (message[i] != ',') {
        str_mode += message[i];
        i++;
    }
    i++;
    while (message[i] != ';') {
        str_players += message[i];
        i++;
    }
    i++;

    GameInfo gameInfo;
    gameInfo.port = stoi(str_port);
    gameInfo.gameMode = str_mode;
    gameInfo.players = str_players;

    allGames.push_back(gameInfo);

    return i;
}
