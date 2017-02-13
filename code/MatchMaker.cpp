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

void MatchMaker::addPlayerToPendingMatch(int id, std::string mode) {
    PendingMatch match = getMatch(mode);
    match.add_player_to_queue(id);
    if (match.is_full()) {
        launchMatch(match); // Ici il faut que ça passe par valeur pour que ça marche
        match.clear();
    }
}


void MatchMaker::run() { std::cout << "hi" << std::endl; }

void MatchMaker::getNewClients() {
    /*
     * Je me souviens plus ce qu'un avait dit que faisait cette fct -_- elle fait un receive c'est ça ?
     *
    */
}

void MatchMaker::getPendingMatches(std::string mode) {


}

void MatchMaker::addPendingMatch(std::string mode) {}

void announceMatchStart(int player){
    //TODO
    /*
     * Un truc du genre:
     * send_message(player, MATCHSTARTING) //Ou MATCHSTARTING serait un nombre (par exemple 32) et du coté du MainManager
     *                                     // on saurait que 32 veut dire afficher :"La partie va commencer"
     *                                     //Je ferais ca demain je suis fatigué
     */
}
