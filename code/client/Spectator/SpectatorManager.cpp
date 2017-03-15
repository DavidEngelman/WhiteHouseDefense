#include "SpectatorManager.hpp"
#include "SpectatorGUI.hpp"
#include "SpectatorConsoleUI.hpp"
#include "../../common/Constants.h"

SpectatorManager::SpectatorManager(int port, App *master_app) :
        NetworkedManager(port, master_app) {

    if (!isConsole) {
        spectatorUI = new SpectatorGUI(this);
    } else {
        spectatorUI = new SpectatorConsoleUI(this);
    }
}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    receive_message(server_socket, buffer); //receive all the games in progress

    //TODO REMPLACER CA PAR parse_message_from_server(buffer);
    parse_message_from_server("5557,classic,bibi,baba,bobo,bubu;5558,classic,lala,lili,lolo,lele;");

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();
    //Selection de la partie et du joueur a support
    spectatorUI->selectGameAndPlayerProcess();

}

void SpectatorManager::connectToGame(int &gamePort, std::string &playerToSupport) {

    std::cout << "ca marche" << std::endl;

    /* On dit au gameServer qu'on veut etre spectateur */
    int game_server_socket_fd = init_connection_to_server(master_app->get_ip(), gamePort);

    // Structure of command: "SUPPORT_PLAYER_STRING,bob;"
    std::string message = SUPPORT_PLAYER_STRING + ","
                          + playerToSupport + ";";
    send_message(game_server_socket_fd, message.c_str());

    // Puis on lance le GameManager
    // GameManager *gameManager = new GameManager(game_server_socket_fd, true, master_app);
    //master_app->transition(gameManager);


}

void SpectatorManager::parse_message_from_server(const std::string &message) {
    int i = 0;
    while (i < message.size()) {
        i = createGameInfo(message, i);
    }
}

int SpectatorManager::createGameInfo(const std::string &message, int &i) {
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
    for (int j = 0; j < 4; ++j) {
        while ((message[i] != ';') && (message[i] != ',')) {
            str_player += message[i];
            i++;
        }
        gameInfo.getPlayers().push_back(str_player);
        i++;
        str_player = "";
    }


    i++;
//"5557,classic,bibi,baba,bobo,bubu;5558,classic,lala,lili,lolo,lele;"

    gameInfo.setPort(stoi(str_port));
    gameInfo.setGameMode(str_mode);
    //gameInfo.players = str_players;

    allGames.push_back(gameInfo);

    spectatorUI->addGame(gameInfo);

    return i;
}

SpectatorManager::~SpectatorManager() {
    spectatorUI->destroy();
}

void SpectatorManager::goToMainMenu() {
    MainManager * mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}

void SpectatorManager::setGameSelected(int game_num) {
    gameSelected = game_num;

}

void SpectatorManager::setPlayerSelected(std::string player_name) {
    playerSelected = player_name;
}

int SpectatorManager::getGameSelected() {
    return gameSelected;
}

std::string &SpectatorManager::getPlayerSelected() {
    return playerSelected;
}

