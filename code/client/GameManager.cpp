

#include "GameManager.hpp"


GameManager::GameManager(char* ip_addr, int port, int id, std::string username, App* app) :
        NetworkedManager(port, ip_addr, app), player_id(id), player_username(username) {}


void GameManager::placeTower(){
    std::string coord;
    gameUI.display();
    coord = gameUI.getCoordTower();
    //send_message(server_socket, coord.c_str());
}

void GameManager::displayWave() {
    gameUI.display();

}

void GameManager::come_back_to_menu(){
    MainManager * menu_manager = new MainManager(server_ip_address, player_id, player_username, my_master_app);
    my_master_app->transition(menu_manager);


}