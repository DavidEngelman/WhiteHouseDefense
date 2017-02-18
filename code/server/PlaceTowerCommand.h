#ifndef PROJET_PLACETOWERCOMMAND_H
#define PROJET_PLACETOWERCOMMAND_H

#include "../common/Position.hpp"

class PlaceTowerCommand {
private:
    Position position;
    int player_id;
public:
    PlaceTowerCommand(int x, int y, int player_id);

    PlaceTowerCommand(Position position, int player_id);

    Position &getPosition();

    int getPlayerID();
};


#endif //PROJET_PLACETOWERCOMMAND_H
