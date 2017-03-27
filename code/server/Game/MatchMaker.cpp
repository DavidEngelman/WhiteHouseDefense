#include <vector>
#include "MatchMaker.hpp"


MatchMaker::MatchMaker(int port) : Server(port),
                                   classicPendingMatch(PendingMatch(CLASSIC_MODE)),
                                   timedPendingMatch(PendingMatch(TIMED_MODE)),
                                   teamPendingMatch(PendingMatch(TEAM_MODE)),
                                   current_server_port(5556) {};

void *MatchMaker::client_handler(int client) {
    get_and_process_command(client);

}

void MatchMaker::run() {
    start_socket_listen();
    int client_socket_fd;

    while (1) {
        client_socket_fd = accept_connection();
        std::thread t1(&MatchMaker::client_handler, this, client_socket_fd);
        t1.detach();
    }
}

void MatchMaker::get_and_process_command(int socket_fd) {
    char command_buffer[BUFFER_SIZE];
    bool communication_over = false;

    while (!communication_over) {
        receive_message(socket_fd, command_buffer);
        Command command;
        command.parse(command_buffer);
        std::string action = command.getAction();

        if (action == GAME_IN_PROGRESS_REQUEST) {
            handleRequestFromSpectator(socket_fd);

        } else if (action == POP_GAME_REQUEST) {
            const std::string &port = command.getNextToken();
            removeGameFromGamesInProgress(stoi(port));
            communication_over = true;

        } else if (action == LEAVE_QUEUE_REQUEST) {
            std::cout << command.getAction() << std::endl;
            removePlayerFromQueue(command.getNextToken(), socket_fd);
            communication_over = true;

        } else if (action == GAME_STARTED_STRING) {
            communication_over = true;

        } else if (action == COMMUNICATION_OVER) {
            communication_over = true;

        } else if (action == EMPTY_REQUEST){
            communication_over = true;
        }
        else {
            MatchmakingCommand matchmakingCommand(socket_fd);
            matchmakingCommand.parse(command_buffer);
            addPlayerToPendingMatch(matchmakingCommand.getPlayerConnection(), matchmakingCommand.getMode());
        }
    }
}

void MatchMaker::handleRequestFromSpectator(int socket_fd) {
    std::string stringToSend;
    for (GameServer *gameServer : activeGames) {
        stringToSend += std::to_string(gameServer->getPort()) + ",";
        stringToSend += gameServer->getMode() + ",";
        stringToSend += gameServer->getAllPlayers();
    }

    send_message(socket_fd, stringToSend.c_str());
}

// Returns True if the match is full and a game is created, False otherwise
void MatchMaker::addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode) {
    PendingMatch &match = getMatch(mode);
    match.add_player_to_queue(player_connection);
    std::cout << "[MATCHMAKER]" <<
              "The match " << mode << " now has " << match.getPlayerConnections().size() << " players" << std::endl;

    if (match.is_full()) {
        launchMatch(match); // Ici il faut que ça passe par valeur pour que ça marche
        match.clear();
    }
}

PendingMatch &MatchMaker::getMatch(std::string mode) {
    if (mode == CLASSIC_MODE) {
        return classicPendingMatch;
    } else if (mode == TIMED_MODE) {
        return timedPendingMatch;
    } else if (mode == TEAM_MODE) {
        return teamPendingMatch;
    } else {
        perror("Invalid match mode");
    }
}


void MatchMaker::launchMatch(PendingMatch match) {
    ++current_server_port;
    launchGameServerThread(match);
    const std::vector<PlayerConnection> &players = match.getPlayerConnections();
    for (auto iterator = players.begin(); iterator != players.end(); iterator++) {
        announceMatchStart(*iterator);
    }
}

void MatchMaker::launchGameServer(PendingMatch match) {
    GameServer *game_server = new GameServer(current_server_port, match.getPlayerConnections(), match.getMode());
    activeGames.push_back(game_server);
    game_server->run();
}

void MatchMaker::launchGameServerThread(PendingMatch &match) {

    std::thread t1(&MatchMaker::launchGameServer, this, match);
    t1.detach();

}

void MatchMaker::announceMatchStart(PlayerConnection playerConnection) {
    send_message(playerConnection.getSocketFd(), GAME_STARTING_STRING.c_str());
    send_data(playerConnection.getSocketFd(), (char *) &current_server_port, sizeof(int));
}

void MatchMaker::removeGameFromGamesInProgress(int port) {
    std::vector<GameServer *>::iterator gameserverIter;
    for (gameserverIter = activeGames.begin(); gameserverIter != activeGames.end(); gameserverIter++) {
        if ((*gameserverIter)->getPort() == port) {
            for (PlayerConnection &pc : (*gameserverIter)->getPlayerConnections()) {
                close(pc.getSocketFd());
            }
            activeGames.erase(gameserverIter);
            break;
        }
    }
}

void MatchMaker::removePlayerFromQueue(std::string mode, int socket) {
    if (mode == CLASSIC_MODE) {
        removePlayerFromMatch(classicPendingMatch, socket);
    } else if (mode == TEAM_MODE) {
        removePlayerFromMatch(teamPendingMatch, socket);
    } else {
        removePlayerFromMatch(timedPendingMatch, socket);
    }

}

void MatchMaker::removePlayerFromMatch(PendingMatch &match, int socket) {
    for (PlayerConnection &pc : match.getPlayerConnections()) {
        if (pc.getSocketFd() == socket) {
            match.remove_player_from_queue(pc);
            break;
        }
    }
    send_message(socket, "removed");
}



