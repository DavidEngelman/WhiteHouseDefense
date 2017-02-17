#include "MatchMaker.hpp"

MatchMaker::MatchMaker(int port) : Server(port),
        // Pas sur que ça marche et que ça continue à exister après
        // la fin du constructeur (faudra peut etre mettre sur le heap)
        // TODO: à verifier
                                   classicPendingMatch(PendingMatch(CLASSIC_MODE)),
                                   timedPendingMatch(PendingMatch(TIMED_MODE)),
                                   teamPendingMatch(PendingMatch(TEAM_MODE)) {
    std::cout << "Constructor" << std::endl;
    //Nice print
};

void MatchMaker::run() {
    while(1){
        int client_socket_fd = accept_connection();
        std::cout << "New client in the matchmaking" << std::endl;

        if (!fork()){
            get_and_process_command(client_socket_fd);
        }
    }
}

void MatchMaker::get_and_process_command(int socket_fd){
    char command_buffer[BUFFER_SIZE];
    receive_message(socket_fd, command_buffer);

    MatchmakingCommand matchmakingCommand(socket_fd);
    matchmakingCommand.parse(command_buffer);

    addPlayerToPendingMatch(matchmakingCommand.getPlayerConnection(), matchmakingCommand.getMode());
}

void MatchMaker::addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode) {
    PendingMatch match = getMatch(mode);
    match.add_player_to_queue(player_connection);
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
    launchGameServer(match);
    const std::vector<PlayerConnection> &players = match.getPlayerConnections();
    for (auto iterator = players.begin(); iterator != players.end(); iterator++){
        announceMatchStart(*iterator);
    }
}

void MatchMaker::launchGameServer(PendingMatch match){
    // TODO: completer une fois qu'il y a la classe GameServer
}

void MatchMaker::announceMatchStart(PlayerConnection playerConnection){
    //TODO
    /*
     * Un truc du genre:
     * send_message(player, MATCHSTARTING) //Ou MATCHSTARTING serait un nombre (par exemple 32) et du coté du MainManager
     *                                     // on saurait que 32 veut dire afficher :"La partie va commencer"
     *                                     //Je ferais ca demain je suis fatigué
     */
    // Pour l'instant, ça envoie un bete string

    // TODO: si il y a plusieurs servers de jeu d'un meme mode, il faudra trouver un moyen de
    // lui signaler vers lequel il doit parler

    send_message(playerConnection.socket_fd, GAME_STARTING_STRING);
}
