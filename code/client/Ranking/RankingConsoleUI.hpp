
#ifndef __RANKINGUI__
#define __RANKINGUI__

#include <string>
#include <iostream>
#include "../Abstract/AbstractConsoleUI.hpp"
#include "../../common/RankingInfos.h"
#include "RankingUI.h"

class RankingConsoleUI : public AbstractConsoleUI, public RankingUI {


public:
	RankingConsoleUI(RankingManager *rankingManager);
    void display(std::vector<RankingInfos> &ranking) override ;
	
};

#endif