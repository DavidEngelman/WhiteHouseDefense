#include "SpectatorManager.hpp"
#include "SpectatorGUI.hpp"
#include "SpectatorConsoleUI.hpp"

SpectatorManager::SpectatorManager(int port, App *master_app) :
        NetworkedManager(port, master_app) {
    if (!isConsole) {
        spectatorUI = new SpectatorGUI(this, master_app->getMainWindow());
    } else {
        spectatorUI = new SpectatorConsoleUI(this);
    }

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();
    spectatorUI->displayAndSelectGameAndPlayer(&allGames); // Will call connectToGame once done
}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    receive_message(server_socket, buffer); //receive all the games in progress

    parse_message_from_server(buffer);
}

void SpectatorManager::connectToGame(GameInfo &game, std::string &playerToSupport) {
    /* On dit au gameServer qu'on veut etre spectateur */
    int game_server_socket_fd = init_connection_to_server(master_app->getIp(), game.getPort());

    // Structure of command: "SUPPORT_PLAYER_STRING,bob;"
    std::string message = SUPPORT_PLAYER_STRING + ","
                          + playerToSupport + ";";
    send_message(game_server_socket_fd, message.c_str());

    //Puis on lance le GameManager
    master_app->launchSupporter(game_server_socket_fd);
}

void SpectatorManager::parse_message_from_server(const std::string &message) {
    int messageIndex = 0;
    while (messageIndex < message.size()) {
        messageIndex = parseGameInfoAndAddToGames(message, messageIndex);
    }
}

int SpectatorManager::parseGameInfoAndAddToGames(const std::string &message, int &i) {

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

    gameInfo.setPort(stoi(str_port));
    gameInfo.setGameMode(str_mode);
    //gameInfo.players = str_players;

    allGames.push_back(gameInfo);
    return i;
}

SpectatorManager::~SpectatorManager() {
    spectatorUI->destroy();
}

void SpectatorManager::goToMainMenu() {
    MainManager *mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}


std::vector<GameInfo> SpectatorManager::getGames() {
    return allGames;
}