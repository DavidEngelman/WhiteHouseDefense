
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__

#include "Manager.hpp"
#include "RankingUI.hpp"
#include "Networking.h"

class RankingManager : public Manager  {

private:
	RankingUI rankingUI;

public:
	std::string getRanking();
	void sendRequest();
};

#endif