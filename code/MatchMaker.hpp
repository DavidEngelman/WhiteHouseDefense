#include "Server.hpp"
#include "PendingMatch.h"
#include "MatchmakingCommand.hpp"

#include <iostream>
#include <string>
#include <vector>

#define CLASSIC_MODE "Classic"
#define TIMED_MODE "Timed"
#define TEAM_MODE "Team"

struct Command{
    std::string mode;
    int player_id;
};

#define GAME_STARTING_STRING "GameStarting"

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

    void addPlayerToPendingMatch(PlayerConnection player_connection, std::string mode);

    PendingMatch &getMatch(std::string mode);

    void launchMatch(PendingMatch match);

    void launchGameServer(PendingMatch match);

    void announceMatchStart(PlayerConnection playerConnection);

public:
    MatchMaker(int port);

    void run() override;
};
