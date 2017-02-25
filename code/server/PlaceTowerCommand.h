#ifndef PROJET_PLACETOWERCOMMAND_H
#define PROJET_PLACETOWERCOMMAND_H

#include "../common/Position.hpp"
#include "Command.hpp"
#include <string>


class PlaceTowerCommand : public Command {
private:
    int player_quadrant;
    Position position;
    std::string tower_type;
public:
    PlaceTowerCommand();

    Position &getPosition();

    int getPlayerQuadrant();

    std::string& getTowerType();

    void parse(char *data) override;

    ~PlaceTowerCommand() = default;
};


#endif //PROJET_PLACETOWERCOMMAND_H
