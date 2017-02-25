

#include "GameManager.hpp"
#include "../server/Server.hpp"


GameManager::GameManager(char *ip_addr, int port, int id, std::string username, App *app) :
        NetworkedManager(port, ip_addr, app), player_id(id), player_username(username),
        phase(PLACING_TOWER),
        gameState(getMapSeedFromServer()),
        gameUI(GameUI(gameState.getMap())) {}


void GameManager::placeTower() {
    if (gameUI.isBuyingTower()) {
        gameUI.display();
        Position pos = gameUI.getPosBuyingTower();
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

    //1) receive seed and adapt the map
    char seed[BUFFER_SIZE];
    receive_message(server_socket, seed);
    gameUI.setSeed(atoi(seed));
    gameUI.display();

    //2) receive phase message
    char phase[BUFFER_SIZE];
    receive_message(server_socket, phase);

    //3) run the phase
    if (strcmp(phase, PLACING_TOWER) == 0) {
        placeTower();
    } else {
        //TODO faire les vagues d'ennemis et afficher à l'écran
    }

    //4) on recommence au point 2)
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
