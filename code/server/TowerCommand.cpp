
#include "TowerCommand.h"


void TowerCommand::parse(char *data) {
    // parse une une chaine de caractere de la forme (place_tower,tower_type,10,14;)

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
    tower_position.setCoord_x(std::stoi(coord_x));
    tower_position.setCoord_y(std::stoi(coord_y));
}

