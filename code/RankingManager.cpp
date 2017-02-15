
#include "RankingManager.hpp"

void RankingManager::sendRequest() {
    std::string message = "ranking;";
    send_message(server_socket, message.c_str()); //send command to server
}

std::string RankingManager::getRanking() {
    char* buffer;
    receive_message(server_socket, buffer); //receive the ranking send by AccountServer
    return std::string(buffer);

}

