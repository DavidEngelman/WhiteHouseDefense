
#include "NetworkedManager.hpp"

NetworkedManager::NetworkedManager(int port, char* address, App* my_app) :AbstractManager(address, my_app), port(port) {
    server_socket  = init_connection_to_server(address, port);
}


NetworkedManager::~NetworkedManager() {
//    close(server_socket);
}


