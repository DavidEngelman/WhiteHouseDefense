#ifndef PROJET_PENDINGMATCH_H
#define PROJET_PENDINGMATCH_H

#include <vector>
#include <string>
#include <algorithm>

class PendingMatch {

private:

    std::string mode;

    // Faudra indiquer ce que represente le int
    // 1) Numero du socket
    // 2) Numero du joueur dans la partie
    // 3) ID du joueur
    // ????
    std::vector<int> queue;

public:

    PendingMatch(std::string modeName);

    const std::string &getMode() const;
    const std::vector<int> &getQueue() const;


    void add_player_to_queue     (int id); //suis pas sur id ou username
    void remove_player_from_queue(int id);
    bool is_full();
};


#endif //PROJET_PENDINGMATCH_H
