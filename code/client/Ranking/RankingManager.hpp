
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__
#define MAX_BUFF_SIZE 1000


#include "../NetworkedManager.hpp"
#include "RankingUI.hpp"
#include "../../common/Networking.h"
#include "../App.hpp"
#include "../../common/RankingInfos.h"
#include "RankingGUI.hpp"

class RankingManager : public NetworkedManager  {

private:
	RankingUI rankingUI;
	RankingGUI *rankingGUI;

public:
	RankingManager(int port, App* my_app);
	std::string getRanking();
	void sendRequest();
	std::vector<RankingInfos> createRanking(std::string);
	void run() override;

};

#endif