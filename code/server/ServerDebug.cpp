#include "GameServer.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<PlayerConnection> playerConnections;
    GameServer gameServer = GameServer(5555, playerConnections);
    gameServer.run();

    return 0;
}
