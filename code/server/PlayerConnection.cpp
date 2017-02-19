//
//

#include "PlayerConnection.hpp"
#include "../common/Networking.h" //for close

int PlayerConnection::getPlayer_id() const {
    return player_id;
}

int PlayerConnection::getSocket_fd() const {
    return socket_fd;
}

void PlayerConnection::setPlayer_id(int player_id) {
    PlayerConnection::player_id = player_id;
}

void PlayerConnection::setSocket_fd(int socket_fd) {
    PlayerConnection::socket_fd = socket_fd;
}


bool PlayerConnection::operator==(const PlayerConnection &rhs) const {
    return player_id == rhs.player_id;
}

bool PlayerConnection::operator!=(const PlayerConnection &rhs) const {
    return !(rhs == *this);
}

PlayerConnection::~PlayerConnection() {
    close(socket_fd);
}