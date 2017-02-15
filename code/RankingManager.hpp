
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__

#include "Manager.hpp"
#include "RankingUI.hpp"
#include "Networking.h"

class RankingManager : public Manager  {

private:
	RankingUI rankingUI;

public:
	RankingManager(int port, char* address);
	std::string getRanking();
	void sendRequest();
	std::string createRanking(std::string);
};

#endif