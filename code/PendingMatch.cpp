//
// Created by benjamin on 13/02/17.
//

#include "PendingMatch.h"

PendingMatch::PendingMatch(std::string modeName) : mode(modeName) {}

const std::string &PendingMatch::getMode() const {
    return mode;
}

const std::vector<int> &PendingMatch::getQueue() const {
    return queue;
}

void PendingMatch::add_player_to_queue(int id) {
    queue.push_back(id);
}

void PendingMatch::remove_player_from_queue(int id) {
    queue.erase(std::remove(queue.begin(), queue.end(), id));
}

void PendingMatch::clear() {
    queue.clear();
}

bool PendingMatch::is_full(){
    return (queue.size() == MAX_SIZE);
}