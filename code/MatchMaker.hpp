#include "Server.hpp"
#include "PendingMatch.h"

#include <iostream>
#include <string>
#include <vector>

#define CLASSIC_MODE "Classic"
#define TIMED_MODE "Timed"
#define TEAM_MODE "Team"

class MatchMaker : public Server {

private:

    PendingMatch classicPendingMatch;
    PendingMatch timedPendingMatch;
    PendingMatch teamPendingMatch;

    // Je sais pas si c'est peut etre pas mieux 3 listes, une pour chaque
    // mode de jeu

    // Pourquoi est-ce qu'il faut 3 listes?
    // Ca ne suffirait pas d'avoir un
    // mode1PendingMatch
    // mode2PendingMatch
    // mode3PendingMatch
    // (J'ai oublié le nom des modes, mais ça devrait etre qq chose ddu genre)

    //hein oui je sais pas pq j'ai dit ça :D


// genre, ce n'est qu'une suggestion, fait revert si tu veux :)
    // n'aie pas peur d'enlever 
    /*
     * Ce qui suit n'est que du pseudocode, donc c'est juste un prototype
     * ça risque de changer pas mal, si on se rend compte que l'organization
     * est debile et meme pas digne d'un singe avec 5 points de QI
     */

    void addPlayerToPendingMatch(int id, std::string mode) {
        PendingMatch match = getMatch(mode);
        match.add_player_to_queue(id);
        if (match.is_full()) {
            launchMatch(match); // Ici il faut que ça passe par valeur pour que ça marche
            match.clear();
        }
    }

    PendingMatch &getMatch(std::string mode) {
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

    void launchMatch(PendingMatch match) {
        /* PseudoCode:
    creataGameServer(match);
    for (int player in match.player) {
        announceMatchStart(player, match);

    }
    */
    }

public:
    MatchMaker(int port) {
        // Pas sur que ça marche et que ça continue à exister après la fin de la fonction
        // TODO: à verifier
        classicPendingMatch = PendingMatch(CLASSIC_MODE);
        timedPendingMatch = PendingMatch(TIMED_MODE);
        teamPendingMatch = PendingMatch(TEAM_MODE);
    };


    void run() override;

    void getNewClients();

    // Ces 2 methodes sont supposé faire quoi?
    void getPendingMatches(std::string mode);

    // Il ne faudra pas ajouter des joueurs dans la signature
    // Ça sert à quoi cette function 
    void addPendingMatch(std::string mode);
};
