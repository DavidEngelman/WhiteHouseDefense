
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__
#define MAX_BUFF_SIZE 1000


#include "../NetworkedManager.hpp"
#include "../../common/Networking.h"
#include "../App.hpp"
#include "../../common/RankingInfos.h"
#include "RankingUI.h"

class RankingUI;

class RankingManager : public NetworkedManager  {

private:
	RankingUI *rankingUI;

public:
	RankingManager(int port, App* my_app);
	~RankingManager();
	std::string getRanking();
	void sendRequest();
	std::vector<RankingInfos> createRanking(std::string);
	void run() override;

	void goToMainMenu();
};

#endif