
#ifndef __RANKINGUI__
#define __RANKINGUI__

#include <string>
#include <iostream>
#include "../Abstract/AbstractUI.hpp"

class RankingUI : public AbstractUI {


public:
	RankingUI() = default;
	void display(std::string ranking);
	
};

#endif