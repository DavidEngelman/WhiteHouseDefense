#include "App.hpp"
#include "WelcomeManager.h"
#include "GameManager.hpp"

/* tmp
App::App(char* server_ip_addr) : current_manager(new WelcomeManager(server_ip_addr, this)){
    current_manager->run();
}
*/

// tmp
App::App(char* server_ip_addr) : current_manager(new GameManager(server_ip_addr, 5556, 0, "Jepsiko" , this)){
    current_manager->run();
}

void App::transition(AbstractManager *new_manager) {
    delete(current_manager);
    current_manager = new_manager;
    current_manager->run();
}
