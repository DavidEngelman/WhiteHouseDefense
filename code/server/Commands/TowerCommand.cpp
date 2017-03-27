#include "TowerCommand.hpp"

int TowerCommand::getPlayerQuadrant() {
    return player_quadrant;
}

Position &TowerCommand::getPosition() {
    return position;
}

std::string &TowerCommand::getTowerType() {
    return tower_type;
}

void TowerCommand::parse(char *data) {
    // parse une une chaine de caractere de la forme "PlaceTower,player_quadrant,tower_type,10,14;"

    Command::parse(data); // Parse l'action

    player_quadrant = std::stoi(getNextToken());
    tower_type = getNextToken();
    position.setX(std::stoi(getNextToken()));
    position.setY(std::stoi(getNextToken()));
}

TowerCommand::TowerCommand() : position(Position(-1, -1)) // Position bidon
{

}

