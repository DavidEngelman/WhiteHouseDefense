
#include "RankingManager.hpp"
#include "../Main/MainManager.hpp"

RankingManager::RankingManager(int port, App *my_app) : NetworkedManager(port, my_app),
                                                        rankingGUI(new RankingGUI(this)) {}

void RankingManager::sendRequest() {
    std::string message = "ranking;";
    send_message(server_socket, message.c_str()); //send command to server
}

std::string RankingManager::getRanking() {
    sendRequest();

    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer); //receive the ranking send by AccountServer
                                            //format : "usr,nbVictories|usr,nbVictories|...|
    return std::string(buffer);

}

std::vector<RankingInfos> RankingManager::createRanking(std::string message_from_server) {

    /* Transforme le message recu du serveur pour etre affiché au client */

    std::vector<RankingInfos> ranking;
    RankingInfos infos;
    std::string message;
    int i = 0;

    while (i < message_from_server.size()){

        if (message_from_server[i] == ','){
            infos.username = message;
            message = "";
            i++;
        }

        if (message_from_server[i] == '|'){
            infos.victories = stoi(message);
            ranking.push_back(infos);
            message = "";
            i++;
        }

        else{
            message+= message_from_server[i];
            i++;
        }
    }

    return ranking;

}

void RankingManager::run() {
    std::vector<RankingInfos> ranking = createRanking(getRanking());

    if (isConsole) {
        rankingUI.display(ranking);

        MainManager *mainManager = new MainManager(5555, master_app);
        master_app->transition(mainManager);
    } else {
        rankingGUI->display(ranking);
    }
}


