#ifndef PROJET_QMATCHMAKINGTHREAD_HPP
#define PROJET_QMATCHMAKINGTHREAD_HPP


#include <QtCore/QThread>
#include <assert.h>
#include <iostream>
#include "../../common/Networking.hpp"
#include "../../common/Strings.hpp"
#include "../../common/Constants.hpp"

class QMatchMakingThread : public QThread {
Q_OBJECT

private:
    std::string mode;
    int id;
    char *ip;
    std::string username;
    int serverSocket;
    bool abort;

signals:

    void gameIsReady(int gameServerPort);

public:

    QMatchMakingThread(std::string mode, int id, char *ip, std::string username, QObject *parent) :
            QThread(parent), mode(mode), id(id), ip(ip), username(username), abort(false) {};

    void run() Q_DECL_OVERRIDE {
        serverSocket = init_connection_to_server(ip, MATCHMAKER_SERVER_PORT);
        char server_response[20] = "HOHOHOHOHOHOHOHOHOH";

        std::string message = mode + ","
                              + std::to_string(id) + ","
                              + username + ";";
        send_message(serverSocket, message.c_str());


        receive_message(serverSocket, server_response);
        // Si App a appellé quitMatchmaking, le flag abort vaut True et le run sort du receive.
        // Alors, si le flag abort est True, on doit annuler le matchmaking et quitter le thread.
        // On fait donc return, pour que le run finisse et le thread soit terminé
        if (abort) return;

        // Comme le reste de la communication se fait en chaine, tres rapidement, il est presque
        // impossible que l'utilisateur appuye sur Leave Queue pile à ce moment la (quelques milisecondes),
        // donc on ne gere pas ce cas. Idealement, on ne créerait pas un sous-classe de QtThread, mais
        // c'est pas tres prioritaire, donc on va se concentrer sur d'autres choses avant

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

    void quitMatchmaking() {
        std::string message = LEAVE_QUEUE_REQUEST + ',' + mode + ';';
        send_message(serverSocket, message.c_str());
        abort = true;
        quit();
    };
};

#endif //PROJET_QMATCHMAKINGTHREAD_HPP
