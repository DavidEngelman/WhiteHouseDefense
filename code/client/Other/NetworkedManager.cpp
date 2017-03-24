
#include "NetworkedManager.hpp"
#include "../../common/Other/Strings.hpp"

NetworkedManager::NetworkedManager(int port, App* my_app) :AbstractManager(my_app), port(port) {
    server_socket  = init_connection_to_server(my_app->getIp(), port);
}


NetworkedManager::~NetworkedManager() {
    send_message(server_socket, COMMUNICATION_OVER.c_str());

}


