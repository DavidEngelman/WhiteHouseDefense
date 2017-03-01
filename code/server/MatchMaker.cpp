#include <thread>
#include "MatchMaker.hpp"
#include "GameServer.hpp"

MatchMaker::MatchMaker(int port) : Server(port),
                                   classicPendingMatch(PendingMatch(CLASSIC_MODE)),
                                   timedPendingMatch(PendingMatch(TIMED_MODE)),
                                   teamPendingMatch(PendingMatch(TEAM_MODE)),
                                   current_server_port(5556){
    std::cout << "Constructor" << std::endl;
};



void MatchMaker::run() {
    start_socket_listen();
    int client_socket_fd;

    while (1) {

        client_socket_fd = accept_connection();
        std::cout << "New client in the matchmaking" << std::endl;

        // TODO: demander à l'assistant si il faut toujours des threads/forks pour processus
        // Fork est pas bon ici
        // Utiliser threads
        get_and_process_command(client_socket_fd);
    }
}

void MatchMaker::get_and_process_command(int socket_fd) {
    char command_buffer[BUFFER_SIZE];
    receive_message(socket_fd, command_buffer);

    Command command;
    command.parse(command_buffer);

    if (command.getAction() == GAME_IN_PROGRESS_REQUEST) {
        handleRequestFromSpectator(socket_fd);
    } else {
        MatchmakingCommand matchmakingCommand(socket_fd);
        matchmakingCommand.parse(command_buffer);

        addPlayerToPendingMatch(matchmakingCommand.getPlayerConnection(), matchmakingCommand.getMode());
    }
}

void MatchMaker::handleRequestFromSpectator(int socket_fd) {
    std::string stringToSend;
    for( GameServer* gameServer : activeGames) {
        stringToSend += std::to_string(gameServer->getPort()) + ",";
        stringToSend += gameServer->getMode() + ",";
        stringToSend += gameServer->getAllPlayers() + ";";
    }

    send_message(socket_fd, stringToSend.c_str());
}

void MatchMaker::addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode) {
    PendingMatch& match = getMatch(mode);
    match.add_player_to_queue(player_connection);
    std::cout << "player_added" << std::endl;
    std::cout << match.getPlayerConnections().size() << std::endl;

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
        // TODO: give a null return value instead of throwing an exception
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
    GameServer* game_server = new GameServer(current_server_port,  match.getPlayerConnections(), match.getMode());
    game_server->run();
}

void MatchMaker::launchGameServerThread(PendingMatch& match){

    std::thread t1 (&MatchMaker::launchGameServer, this, match);
    t1.detach(); // TODO: bien comprendre et verifier si c'est bien ce qu'on veut

}

void MatchMaker::announceMatchStart(PlayerConnection playerConnection) {
    // TODO: si il y a plusieurs servers de jeu d'un meme mode, il faudra trouver un moyen de
    // lui signaler vers lequel il doit parler

    send_message(playerConnection.getSocket_fd(), GAME_STARTING_STRING);
    send_data(playerConnection.getSocket_fd(), (char *) &current_server_port, sizeof(int));
}
