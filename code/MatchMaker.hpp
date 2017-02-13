#include "Server.hpp"
#include <iostream>
#include <string>
#include <queue>

class MatchMaker : public Server {

private:

	std::queue classicPendingMatches;
    std::queue againstTimePendingMatches;
    std::queue teamPendingMatches;

public:

    MatchMaker(int port);

    void run() override;
	void getNewClients();

	void getPendingMatches(std::string mode);

	void addPendingMatch(std::string mode);
};
