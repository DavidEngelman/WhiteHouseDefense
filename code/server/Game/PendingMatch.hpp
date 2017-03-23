#ifndef PROJET_PENDINGMATCH_H
#define PROJET_PENDINGMATCH_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Other/PlayerConnection.hpp"

#define MAX_SIZE 4

class PendingMatch {

private:
    std::string mode;
    std::vector<PlayerConnection> playerConnections;
public:

    PendingMatch(std::string modeName);

    const std::string &getMode() const;
    std::vector<PlayerConnection> &getPlayerConnections();


    void add_player_to_queue     (PlayerConnection& playerConnection); //suis pas sur id ou username
    void remove_player_from_queue(PlayerConnection& playerConnection);
    bool is_full();

    void clear();
};


#endif //PROJET_PENDINGMATCH_H
