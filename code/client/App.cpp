#include "App.hpp"
#include "LoginManager.hpp"

App::App(char* server_ip_addr)  : current_mamanger(LoginManager(5555, server_ip_addr)){}

void App::transition(AbstractManager new_manager) {
    delete(current_mamanger);
    current_mamanger = new_manager;
    current_mamanger.run();

}