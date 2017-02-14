
#ifndef __RANKINGMANAGER__
#define __RANKINGMANAGER__

#include "Manager.hpp"
#include "RankingUI.hpp"

class RankingManager : public Manager  {

private:
	RankingUI rankingUI;

public:
	void getInfo();
};

#endif