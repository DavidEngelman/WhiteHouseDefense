#ifndef PROJET_RANKINGUI_H
#define PROJET_RANKINGUI_H

#include <vector>
#include "../../common/RankingInfos.h"
#include "../Abstract/AbstractUI.hpp"
#include "RankingManager.hpp"

class RankingManager;

class RankingUI: public virtual AbstractUI {

protected:
    RankingManager *rankingManager;


public:
    RankingUI(RankingManager *rankingManager) : rankingManager(rankingManager) {};
    virtual void display(std::vector<RankingInfos> &ranking) = 0;

};

#endif //PROJET_RANKINGUI_H
