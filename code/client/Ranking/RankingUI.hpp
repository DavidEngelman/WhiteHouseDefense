
#ifndef __RANKINGUI__
#define __RANKINGUI__

#include <string>
#include <iostream>
#include "../Abstract/AbstractUI.hpp"
#include "../../common/RankingInfos.h"

class RankingUI : public AbstractUI {


public:
	RankingUI() = default;
	void display(std::vector<RankingInfos> &ranking);
	
};

#endif