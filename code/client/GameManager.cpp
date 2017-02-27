

#include "GameManager.hpp"
#include "../server/Server.hpp"

//NetworkedManager(port, ip_addr, app)
GameManager::GameManager(char *ip_addr, int port, int socket, int id, std::string username, App *app) :
        AbstractManager(ip_addr, app),
        server_socket(socket),
        player_id(id), player_username(username),
        gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
        {}


void GameManager::placeTower() {
    if (gameUI.isBuyingTower()) {
        gameUI.display(gameState);
        Position pos = gameUI.getPosBuyingTower();
        sendRequest(pos, " " /*demander le type de tour plus haut*/ );
    } else {
        gameUI.display(gameState);
    }
}

void GameManager::displayWave() {
    gameUI.display(gameState);
}

void GameManager::come_back_to_menu() {
    MainManager *menu_manager = new MainManager(server_ip_address, player_id, player_username, master_app);
    master_app->transition(menu_manager);

}

void GameManager::input_thread() {
    while(!stopflag) {
        placeTower();
        stopflag = true;
    }
}

bool GameManager::checkValidity(Position towerPos) {

}

bool GameManager::sendRequest(Position towerPos, std::string towerType) {
    char server_response[10];
    std::string message = towerType + "," + std::to_string(towerPos.getX()) + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    return server_response[0] == '1';
}


void GameManager::run() {
    std::cout << "GameManager Running" << std::endl;
    gameUI.display(gameState);
    char server_msg_buff [BUFFER_SIZE];
    std::cout << "Je suis apres le clear" << std::endl;

    while(1) {
        receive_message(server_socket, server_msg_buff);
        std::cout << "Message: " << server_msg_buff << std::endl;

        if (strcmp(server_msg_buff, PLACING_TOWER) == 0 && is_alive()) {
            //////////
            /* if thread not running {   j'ai un peu de mal avec ces thread en c++ */
            //std::thread input(input_thread);
            /////////
        }else if (strcmp(server_msg_buff, WAVE) == 0){
            //TODO kill InputThread
            std::cout << "Receive start wave signal" << std::endl;
        }
        else{
            unSerializeGameState(server_msg_buff);
            std::cout << "Received game state" << std::endl;

            if ( false && gameState.getIsGameOver()){
                break;
            }
        }
    }


}

void GameManager::unSerializeGameState(char* seriarlized_gamestate){
    std::cout<<"serveur gamestate: "<<seriarlized_gamestate<<std::endl;

    GameState tmp = GameState();
    gameState = tmp;



}

bool GameManager::is_alive() {
    if (gameState.getPlayerStates().size() == 0) return true; // Pas encore recu gameState du server

    bool alive = false;
    for( PlayerState& playerState : gameState.getPlayerStates()){
        if (playerState.getPlayer_id() == player_id){
            if (playerState.getHp() > 0){
                alive = true;
                break;
            }
        }
    }

    return alive;
}

unsigned int GameManager::getMapSeedFromServer() const {
    // Pas génial, mais ça fera l'affaire pour l'instant
    std::cout << "Getting seed" << std::endl;

    char buffer[BUFFER_SIZE];
    receive_message(server_socket, buffer);
    std::cout << "Received string: " << buffer << std::endl;

    std::string action(buffer);
    if (action != SETUP_GAME) {
        std::cout << "Expected action was setup; it was instead " << action << std::endl;
        perror("Incorrect message for seed");
    }



    unsigned int seed;
    receive_data(server_socket, &seed, sizeof(unsigned int));
    std::cout << "Received seed: " << seed << std::endl;
    return seed;
}

int GameManager::getQuadrantFromServer() {
    std::cout << "Getting quadrant" << std::endl;

    int quadrant;
    receive_data(server_socket, &quadrant, sizeof(int));
    return quadrant;
}

int GameManager::getQuadrant() const {
    return quadrant;
}
