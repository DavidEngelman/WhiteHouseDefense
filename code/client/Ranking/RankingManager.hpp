
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__
#define MAX_BUFF_SIZE 1000


#include "../NetworkedManager.hpp"
#include "RankingUI.hpp"
#include "../../common/Networking.h"
#include "../App.hpp"

class RankingManager : public NetworkedManager  {

private:
	RankingUI * rankingUI; // TODO: it's now a pointer

public:
	RankingManager(int port, App* my_app);
	std::string getRanking();
	void sendRequest();
	std::string createRanking(std::string);
	void run() override;

};

#endif