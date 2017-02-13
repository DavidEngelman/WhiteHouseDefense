#include "MatchMaker.hpp"

MatchMaker::MatchMaker(int port) : Server(port) {}

void MatchMaker::run() {std::cout << "hi" << std::endl;}

void MatchMaker::getNewClients() {}

void MatchMaker::getPendingMatches(std::string mode) {}

void MatchMaker::addPendingMatch(std::string mode) {}

