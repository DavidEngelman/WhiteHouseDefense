
#include "NetworkedManager.hpp"
#include "../../common/Other/Strings.hpp"

NetworkedManager::NetworkedManager(int port, App* my_app) :AbstractManager(my_app), port(port) {
    server_socket  = init_connection_to_server(my_app->getIp(), port);

    if (server_socket == -1){
        if (isConsole) {
            std::cout << "Couldn't connect to the server. Exiting..." << std::endl;
            exit(0);
        } else {
            QMessageBox msgBox;
            msgBox.setText("Couldn't connect to the server. Exiting...");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            exit(0);
        }
    }
}


NetworkedManager::~NetworkedManager() {
    send_message(server_socket, COMMUNICATION_OVER.c_str());

}


