#include "App.hpp"
#include "Welcome/WelcomeManager.hpp"
#include "../common/Constants.h"

App::App(char* server_ip_addr) : server_ip_address(server_ip_addr),
    player_id(-1), username("\0"), current_manager(nullptr), main_window(nullptr)
{
     if(!isConsole){
        main_window = new QWidget();
        main_window->setFixedSize(750,600);
        main_window->show();
     }
    current_manager = new WelcomeManager(this);
    current_manager->run();
}

void App::transition(AbstractManager *new_manager) {
    delete(current_manager);
    current_manager = new_manager;
    current_manager->run();
}

char *App::get_ip() {
    return server_ip_address;
}

int App::get_id() {
    return player_id;
}

std::string App::get_username() {
    return username;
}

void App::set_id(int id) {
    player_id = id;
}

void App::set_username(std::string name) {
    username = name;
}

App::~App() {
    if (username == "") { // Si le joeur est connecté, on envoye un message de deconexion
        int socket = init_connection_to_server(server_ip_address, ACCOUNT_SERVER_PORT);
        std::string message = "Exit," + std::to_string(player_id);
        send_message(socket, message.c_str());
    }
}

QWidget *App::getMainWindow() {
    return main_window;
}
