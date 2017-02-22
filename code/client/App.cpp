#include "App.hpp"
#include "WelcomeManager.h"

App::App(char* server_ip_addr) : current_manager(new WelcomeManager(server_ip_addr, this)){
    current_manager->run();
}

void App::transition(AbstractManager *new_manager) {
    delete(current_manager);  // Le bug est declenché par cette ligne
    current_manager = new_manager;
    current_manager->run();

}
