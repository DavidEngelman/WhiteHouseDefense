
#include "NetworkedManager.hpp"

NetworkedManager::NetworkedManager(int port, App* my_app) :AbstractManager(my_app), port(port) {
    server_socket  = init_connection_to_server(my_app->getIp(), port);
}


NetworkedManager::~NetworkedManager() {
//    close(server_socket);
}


