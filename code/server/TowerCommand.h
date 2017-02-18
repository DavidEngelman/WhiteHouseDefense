#include "Command.hpp"
#include "../common/Position.hpp"

#ifndef PROJET_TOWERCOMMAND_H
#define PROJET_TOWERCOMMAND_H


class TowerCommand : public Command {

private:
    std::string tower_type;
    Position tower_position;

public:
    TowerCommand() = default;
    void parse(char* data) override;

    ~TowerCommand() = default;



};


#endif //PROJET_TOWERCOMMAND_H
