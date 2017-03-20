#ifndef PROJET_QMATCHMAKINGTHREAD_HPP
#define PROJET_QMATCHMAKINGTHREAD_HPP


#include <QtCore/QThread>
#include <assert.h>
#include "../../common/Networking.hpp"
#include "../../common/Strings.hpp"

class QMatchMakingThread : public QThread {
Q_OBJECT

private:
    std::string mode;
    int id;
    char * ip;
    std::string username;
    int serverSocket;

signals:
    void gameIsReady(int gameServerPort);

public:

    QMatchMakingThread(std::string mode, int id, char * ip, std::string username, QObject *parent) :
            QThread(parent), mode(mode), id(id), ip(ip), username(username) {};

    void run() Q_DECL_OVERRIDE {
        // TODO: ce code est presque identique à celui de GameLauncher. Faudrait faire un refactoring pour
        // eviter cette repetition
        serverSocket = init_connection_to_server(ip, MATCHMAKER_SERVER_PORT);
        char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

        std::string message = mode + ","
                              + std::to_string(id) + ","
                              + username + ";";
        send_message(serverSocket, message.c_str());


        receive_message(serverSocket, server_response);
        assert(strcmp(server_response, GAME_STARTING_STRING) == 0);

        // TODO: pour l'instant on recoit le port du gameServer, mais ca ne sert a rien pour l'instant
        // parce qu'on communique au GameServer via le socket qu'on avait avec la Matchmaker
        int game_port;
        receive_data(serverSocket, &game_port, sizeof(int));

        // Envoyer au matchmaker un string pour lui dire de ne plus faire receive sur le socket,
        // car c'est maintenant le GameServer qui communique via ce socket
        std::string matchmakerMessage = GAME_STARTED_STRING + ";";
        send_message(serverSocket, matchmakerMessage.c_str());

        emit gameIsReady(serverSocket);
    }
};

#endif //PROJET_QMATCHMAKINGTHREAD_HPP
