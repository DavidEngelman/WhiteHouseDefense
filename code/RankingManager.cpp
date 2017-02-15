
#include "RankingManager.hpp"

RankingManager::RankingManager(int port, char* address): Manager(port, address) {
    sendRequest();
    std::string ranking = createRanking(getRanking());
    rankingUI.display(ranking);
}

void RankingManager::sendRequest() {
    std::string message = "ranking;";
    send_message(server_socket, message.c_str()); //send command to server
}

std::string RankingManager::getRanking() {
    char buffer[1000]; //TODO mettre une constante a la place de 1000
    receive_message(server_socket, buffer); //receive the ranking send by AccountServer
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
            result += " -- ";
            i++;
        }

        if (message_from_server[i] == '|'){

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

