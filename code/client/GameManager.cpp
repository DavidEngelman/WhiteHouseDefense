

#include "GameManager.hpp"
#include "../server/Server.hpp"


GameManager::GameManager(char *ip_addr, int port, int id, std::string username, App *app) :
        NetworkedManager(port, ip_addr, app), player_id(id), player_username(username),
        phase(PLACING_TOWER),
        gameState(getMapSeedFromServer()),  // L'ordre est important parce qu'on fait des
        quadrant(getQuadrantFromServer()),  // recv. Ne pas changer l'ordre!
        gameUI(gameState.getMap())
        {} //Le gamestate n'est pas censé avoir la map


void GameManager::placeTower() {
    if (gameUI.isBuyingTower()) {
        gameUI.display();
        Position pos = gameUI.getPosBuyingTower();
        // TODO: send tower placement command to server
    } else {
        gameUI.display();
    }
    //send_message(server_socket, coord.c_str());
}

void GameManager::displayWave() {
    gameUI.display();
}

void GameManager::come_back_to_menu() {
    MainManager *menu_manager = new MainManager(server_ip_address, player_id, player_username, my_master_app);
    my_master_app->transition(menu_manager);

}

void GameManager::run() {
    gameUI.display();
        char server_msg_buff [BUFFER_SIZE];
    while(1){

        receive_message(server_socket, server_msg_buff);
        if (strcmp(server_msg_buff, PLACING_TOWER) == 0){
            //TODO InputThread
        }
        else if (strcmp(server_msg_buff, WAVE) == 0){
            //TODO kill InputThread
        }
        else{
            //TODO parse GamesState sent from server
            //TODO update gamesState

            if (gameState.getIsGameOver()){
                break;
            }
        }
    }

}

void GameManager::unSerializeGameState(char* seriarlized_gamestate){


}

unsigned int GameManager::getMapSeedFromServer() const {
    // Pas génial, mais ça fera l'affaire pour l'instant

    char buffer[BUFFER_SIZE];
    receive_message(server_socket, buffer);

    std::string action(buffer);
    if (action != "seed") {
        std::cout << "Expected action was seed; it was instead " << action << std::endl;
        perror("Incorrect message for seed");
    }


    unsigned int seed;
    receive_data(server_socket, &seed, sizeof(unsigned int));
    return seed;
}

int GameManager::getQuadrantFromServer() {
    int quadrant;
    receive_data(server_socket, &quadrant, sizeof(int));
    return quadrant;
}

int GameManager::getQuadrant() const {
    return quadrant;
}
