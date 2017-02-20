
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__
#define MAX_BUFF_SIZE 1000


#include "NetworkedManager.hpp"
#include "RankingUI.hpp"
#include "../common/Networking.h"

class RankingManager : public NetworkedManager  {

private:
	RankingUI rankingUI;

public:
	RankingManager(int port, char* address);
	std::string getRanking();
	void sendRequest();
	std::string createRanking(std::string);
	void run() override;

};

#endif