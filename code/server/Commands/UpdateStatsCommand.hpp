#ifndef PROJET_UPDATESTATSCOMMAND_H
#define PROJET_UPDATESTATSCOMMAND_H

#include "../../common/Other/Command.hpp"
#include "../../common/Other/Tools.hpp"


class UpdateStatsCommand: public Command {

private:
    int playerId;
    int pnjKilled;
    bool isWinner;

public:
    void parse(char *data) override;

    int getPlayerId();
    int getPnjKilled();
    bool getIsWinner();

};


#endif //PROJET_UPDATESTATSCOMMAND_H
