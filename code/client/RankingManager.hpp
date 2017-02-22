
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__
#define MAX_BUFF_SIZE 1000


#include "NetworkedManager.hpp"
#include "RankingUI.hpp"
#include "../common/Networking.h"
#include "App.hpp"

class RankingManager : public NetworkedManager  {

private:
	RankingUI rankingUI;
	std::string username;
	int player_id;

public:
	RankingManager(int port, char* address, int player_id, std::string username, App* my_app);
	std::string getRanking();
	void sendRequest();
	std::string createRanking(std::string);
	void run() override;

};

#endif