
#include "RankingManager.hpp"

RankingManager::RankingManager(int port, char* address):
        NetworkedManager(port, address) {}

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

std::string RankingManager::createRanking(std::string message_from_server) {

    /* Transforme le message recu du serveur pour etre affiché au client */

    std::string result = "";
    int i = 0;
    int pos = 1;

    std::cout << pos << ") ";

    while (i < message_from_server.size()){

        if (message_from_server[i] == ','){
            result += "\t\t\t\t\t";
            i++;
        }

        if (message_from_server[i] == '|'){

            result += " victories";

            if (i != message_from_server.size() - 1){

                pos++;
                result+="\n";
                result+=std::to_string(pos);
                result+=") ";
            }
            i++;
        }

        else{
            result+= message_from_server[i];
            i++;
        }
    }

    return result;

}

void RankingManager::run() {
    std::string ranking = createRanking(getRanking());
    rankingUI.display(ranking);
}