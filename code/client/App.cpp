#include "App.hpp"

App::App(char* server_ip_addr)  : current_manager(new WelcomeManager(server_ip_addr)){}

void App::transition(AbstractManager *new_manager) {
    delete(current_manager);
    current_manager = new_manager;
    current_manager->run();

}