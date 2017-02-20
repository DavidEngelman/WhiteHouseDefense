#include "App.hpp"

App::App(char* server_ip_addr) {
    init(server_ip_addr);
}

void App::transition(AbstractManager *new_manager) {
    std::cout << "transition" << std::endl;
    delete(current_manager);
    current_manager = new_manager;
    current_manager->run();

}
void App::init(char* addr) {
    WelcomeManager* welcomeManager = new WelcomeManager(addr);
    transition(welcomeManager);
}