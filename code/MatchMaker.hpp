#include "Server.hpp"
#include "PendingMatch.h"

#include <iostream>
#include <string>
#include <vector>

class MatchMaker : public Server {

private:

    PendingMatch classicPendingMatches;
	PendingMatch againstTimePendingMatches;
	PendingMatch teamPendingMatches;

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
    PendingMatch classicModeMatch;
    PendingMatch timedModeMatch;
    PendingMatch teamModeMatch;

    /*
     * Ce qui suit n'est que du pseudocode, donc c'est juste un prototype
     * ça risque de changer pas mal, si on se rend compte que l'organization
     * est debile et meme pas digne d'un singe avec 5 points de QI
     */

    void addPlayerToPendingMatch(int id, std::string mode) {
    	/*
	PendingMatch match = getMatch(); <- Insert magic here
	
	match.add_player_to_queue(id);
	if (match.is_full()){
             launchMatch(match);
	     removePendingMatch();
	}
	*/
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
    	classicModeMatch = new PendingMatch("Classic");
	timedModeMatch = new PendingMatch("Timed");
	teamModeMatch = new PendingMatch("Team");
    };

    

    void run() override;
    void getNewClients();
	
    // Ces 2 methodes sont supposé faire quoi?
    void getPendingMatches(std::string mode);

    // Il ne faudra pas ajouter des joueurs dans la signature
    // Ça sert à quoi cette function 
    void addPendingMatch(std::string mode);
};
