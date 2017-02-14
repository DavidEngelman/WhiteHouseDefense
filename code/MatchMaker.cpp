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
    /* PseudoCode:
    creataGameServer(match);
    for (int player in match.player) {
        announceMatchStart(player, match);

    }
    */
}

void MatchMaker::addPlayerToPendingMatch(Id id, std::string mode) {
    PendingMatch match = getMatch(mode);
    match.add_player_to_queue(id);
    if (match.is_full()) {
        launchMatch(match); // Ici il faut que ça passe par valeur pour que ça marche
        match.clear();
    }
}


void MatchMaker::run() {

    while(1){
        int newClient = accept_connection();
        std::cout << "New client in the matchmaking" << std::endl;

        if (!fork()){
            char command_buffer[BUFFER_SIZE];
            get_and_process_command(newClient, command_buffer);
        }

    }
}

void MatchMaker::getNewClients() {
    //Je sais pas si c est tres util cette methode

}

void MatchMaker::get_and_process_command(int client_socket, char* command_buffer){
    Command command;
    Id client_id; // (la struct {socket, player_id}

    receive_message(client_socket, command_buffer); // Recois la commande

    parse_command(command_buffer, &command);

    client_id.socket = client_socket;
    client_id.player_id = command.player_id;

    addPlayerToPendingMatch(client_id, command.mode);


}

void MatchMaker::parse_command(char *data, Command *command){
    /*
     * Disons qu'une commande se présente s'envoie dans un string de type : mode,player_id;
     *
     * Ex: si bob veut jouer en classic et que le playerID de bob est 18 -> data = classic,18;
     *
     */
    int i = 0;

    // Extracts mode (ex: classic)
    while (data[i] != ',') {
        command->mode += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the player_id (ex: 18)
    std::string string_player_id;
    while (data[i] != ';') {
        string_player_id += data[i];
        i++;
    }
    command->player_id = atoi(string_player_id); // "18" -> 18

}

void MatchMaker::getPendingMatches(std::string mode) {


}

void MatchMaker::addPendingMatch(std::string mode) {

}

void announceMatchStart(int player){
    //TODO
    /*
     * Un truc du genre:
     * send_message(player, MATCHSTARTING) //Ou MATCHSTARTING serait un nombre (par exemple 32) et du coté du MainManager
     *                                     // on saurait que 32 veut dire afficher :"La partie va commencer"
     *                                     //Je ferais ca demain je suis fatigué
     */
}
