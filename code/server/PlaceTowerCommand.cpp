#include "PlaceTowerCommand.h"

int PlaceTowerCommand::getPlayerID() {
    return player_id;
}

Position &PlaceTowerCommand::getPosition() {
    return Position;
}

PlaceTowerCommand::PlaceTowerCommand(int x, int y, int player_id) :
        position(Position(x, y)), player_id(player_id) {}

PlaceTowerCommand::PlaceTowerCommand(Position position, int player_id) :
        position(position), player_id(player_id) {}