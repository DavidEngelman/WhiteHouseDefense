#include "Server.hpp"
#include "PendingMatch.h"

#include <iostream>
#include <string>
#include <vector>

class MatchMaker : public Server {

private:

    std::vector<PendingMatch> pendingMatches; // Je sais pas si c'est peut etre pas mieux 3 listes, une pour chaque
                                              // mode de jeu

public:

    MatchMaker(int port);

    void run() override;
	void getNewClients();

	void getPendingMatches(std::string mode);

	void addPendingMatch(std::string mode);
};
