#ifndef PROJET_TOWERCOMMAND_H
#define PROJET_TOWERCOMMAND_H

#include "../common/Position.hpp"
#include "../common/Command.hpp"
#include <string>


class TowerCommand : public Command {
private:
    int player_quadrant;
    Position position;
    std::string tower_type;
public:
    TowerCommand();

    Position &getPosition();

    int getPlayerQuadrant();

    std::string& getTowerType();

    void parse(char *data) override;

    ~TowerCommand() = default;
};


#endif //PROJET_TOWERCOMMAND_H
