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

    void addPlayerToPendingMatch(int id, std::string mode);

    PendingMatch &getMatch(std::string mode);

    void launchMatch(PendingMatch match);

public:
    MatchMaker(int port);

    void run() override;

    void getNewClients();

    // Ces 2 methodes sont supposé faire quoi?
    //Je sais plus :/ je pense qu'elles servaient a faire semblant qu'on avait des méthodes dans nos classes
    void getPendingMatches(std::string mode);

    // Il ne faudra pas ajouter des joueurs dans la signature
    // Ça sert à quoi cette function 
    void addPendingMatch(std::string mode); //Celle la elle
};
