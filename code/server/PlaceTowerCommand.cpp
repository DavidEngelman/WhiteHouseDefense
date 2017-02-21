#include "PlaceTowerCommand.h"

int PlaceTowerCommand::getPlayerID() {
    return player_id;
}

Position &PlaceTowerCommand::getPosition() {
    return position;
}

std::string &PlaceTowerCommand::getTowerType() {
    return tower_type;
}

// TODO: ça serait mieux que toutes les methodes parse renvoient un booleen qui indiquent si le
// parse a été successful.
void PlaceTowerCommand::parse(char *data) {
    // parse une une chaine de caractere de la forme "PlaceTower,tower_type,10,14;"
    std::string coord_x, coord_y, type;

    int i = extract_action(data);

    // Extracts tower_type
    while (data[i] != ',') {

        type += data[i];
        i++;
    }
    i++;

    // Extracts the coord_x
    while (data[i] != ',') {

        coord_x += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the coord_y
    while (data[i] != ';') {
        coord_y += data[i];
        i++;
    }

    tower_type = type;
    position.setX(std::stoi(coord_x));
    position.setY(std::stoi(coord_y));
}

PlaceTowerCommand::PlaceTowerCommand() : position(Position(-1, -1)) // Position bidon
{

}

