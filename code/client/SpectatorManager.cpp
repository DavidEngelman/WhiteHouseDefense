#include "SpectatorManager.hpp"

//"5557,classic,bibi,baba,bobo,bubu;5558,classic,lala,lili,lolo,lele;"

SpectatorManager::SpectatorManager(int port, char* address, int id, std::string username, App* master_app) :
        NetworkedManager(port, address, master_app), player_id(id), player_usr_name(username) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    //receive_message(server_socket, buffer); //receive all the games in progress
    parse_message_from_server(std::string(buffer));

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();

    if (allGames.size() == 0){
        spectatorUI.displaySorryMessage();
        MainManager * mng = new MainManager(server_ip_address, player_id, player_usr_name, master_app);
        master_app->transition(mng);

    }
    else{
        spectatorUI.displaySpectatorUI(allGames);
        int gameSelected = spectatorUI.inputSpectatorUI(allGames.size());
        int gamePort = allGames[gameSelected].port;
        GameManager *gameManager = new GameManager(server_ip_address,gamePort,server_socket,
                                                   player_id, player_usr_name, master_app);
        master_app->transition(gameManager);
    }
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

