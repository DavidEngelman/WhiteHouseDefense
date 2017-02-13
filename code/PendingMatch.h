#ifndef PROJET_PENDINGMATCH_H
#define PROJET_PENDINGMATCH_H

#include <vector>
#include <string>
#include <algorithm>

class PendingMatch {

private:

    std::string mode;
    std::vector queue;

public:

    PendingMatch(std::string modeName);

    const std::string &getMode() const;

    const std::vector &getQueue() const;

    void add_player_to_queue(int id); //suis pas sur id ou username
    void remove_player_from_queue(int id);
};


#endif //PROJET_PENDINGMATCH_H
