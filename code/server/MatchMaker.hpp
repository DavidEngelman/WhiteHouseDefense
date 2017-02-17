#ifndef MATCHMAKER_HPP
#define MATCHMAKER_HPP

#include "Server.hpp"
#include <string>

class MatchMaker : public Server {

private:
	int pendingMatches;

public:

	void getNewClients();

	void getPendingMatches(std::string mode);

	void addPendingMatch(std::string mode);
};

#endif
