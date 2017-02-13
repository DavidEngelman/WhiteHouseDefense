#include "Server.hpp"
#include "PendingMatch.h"

#include <iostream>
#include <string>
#include <vector>

class MatchMaker : public Server {

private:

    std::vector<PendingMatch> pendingMatches;
	// Je sais pas si c'est peut etre pas mieux 3 listes, une pour chaque
    // mode de jeu

    // Pourquoi est-ce qu'il faut 3 listes?
    // Ca ne suffirait pas d'avoir un
    // mode1PendingMatch
    // mode2PendingMatch
    // mode3PendingMatch
    // (J'ai oublié le nom des modes, mais ça devrait etre qq chose ddu genre)

public:

    MatchMaker(int port);

    void run() override;
	void getNewClients();

	
	// Ces 2 methodes sont supposé faire quoi?
	void getPendingMatches(std::string mode);

	// Il ne faudra pas ajouter des joueurs dans la signature
	// Ça sert à quoi cette function 
	void addPendingMatch(std::string mode);
};
