#include "SpectatorManager.hpp"


SpectatorManager::SpectatorManager(int port, char* address, int id, std::string username, App* master_app) :
        NetworkedManager(port, address, master_app), player_id(id), player_usr_name(username) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    receive_message(server_socket, buffer); //receive all the games in progress
    parse_message_from_server(buffer);

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();

    if (allGames.size() == 0){
        //Si y a pas de game a spectate -> on pleure
        spectatorUI.displaySorryMessage();
        MainManager * mng = new MainManager(5555,server_ip_address, player_id, player_usr_name, master_app);
        master_app->transition(mng);

    }
    else{
        //Selection de la partie et du jouer a support
        spectatorUI.displaySpectatorUI(allGames);
        int gameSelected = spectatorUI.gameSelection(allGames.size());
        int gamePort = allGames[gameSelected].getPort();
        std::string playerToSupport = spectatorUI.playerSelection(allGames[gameSelected]);

        //Lancement du bordel
        //TODO j'ai pas trop compris ce qu'il faut faire à ce moment précis :(

        /*GameManager *gameManager = new GameManager(server_ip_address,gamePort,server_socket,
                                                   player_id, player_usr_name, master_app);*/
        //master_app->transition(gameManager);
    }
}

void SpectatorManager::parse_message_from_server(const std::string &message) {
    int i = 0;
    while (i < message.size()) {
        i = createGameInfo(message, i);
    }
}

int SpectatorManager::createGameInfo(const std::string& message, int& i) {
    std::string str_port, str_mode, str_player;
    GameInfo gameInfo;

    //extract port
    while (message[i] != ',') {
        str_port += message[i];
        i++;
    }
    i++;

    //extract mode
    while (message[i] != ',') {
        str_mode += message[i];
        i++;
    }
    i++;

    //extract players
    while (message[i] != ';') {

        if (message[i] != ','){
            str_player += message[i];
            i++;
        }
        else{
            gameInfo.getPlayers().push_back(str_player);
            i++;
            str_player = "";
        }


    }
    i++;
//"5557,classic,bibi,baba,bobo,bubu;5558,classic,lala,lili,lolo,lele;"

    gameInfo.setPort(stoi(str_port));
    gameInfo.setGameMode(str_mode);
    //gameInfo.players = str_players;

    allGames.push_back(gameInfo);

    return i;
}

