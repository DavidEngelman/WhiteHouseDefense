#include "SpectatorManager.hpp"


SpectatorManager::SpectatorManager(int port, App *master_app) :
        NetworkedManager(port, master_app) {}

void SpectatorManager::getGamesFromMatchMaker() {
    char buffer[5000];
    send_message(server_socket, "games;");
    receive_message(server_socket, buffer); //receive all the games in progress
    parse_message_from_server(buffer);

}

void SpectatorManager::run() {
    getGamesFromMatchMaker();

    if (allGames.size() == 0) {
        //Si y a pas de game a spectate -> on pleure
        spectatorUI.displaySorryMessage();
        MainManager *mng = new MainManager(master_app);
        master_app->transition(mng);
    } else {
        //Selection de la partie et du jouer a support
        spectatorUI.displaySpectatorUI(allGames);
        int gameSelected = spectatorUI.gameSelection((int) allGames.size());
        int gamePort = allGames[gameSelected].getPort();
        std::string playerToSupport = spectatorUI.playerSelection(allGames[gameSelected]);


        /* On dit au gameServer qu'on veut etre spectateur */
        int game_server_socket_fd = init_connection_to_server(master_app->get_ip(), gamePort);

        // Structure of command: "SUPPORT_PLAYER_STRING,bob;"
        std::string message = SUPPORT_PLAYER_STRING + ","
                              + playerToSupport + ";";
        send_message(game_server_socket_fd, message.c_str());

        // Puis on lance le GameManager
        GameManager *gameManager = new GameManager(game_server_socket_fd, true, master_app);
        master_app->transition(gameManager);
    }
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

    return i;
}

