

#include "GameManager.hpp"
#include "../server/Server.hpp"


//NetworkedManager(port, ip_addr, app)
GameManager::GameManager(char *ip_addr, int port, int socket, int id, std::string username, App *app) :
        AbstractManager(ip_addr, app),
        server_socket(socket),
        player_id(id), player_username(username),
        gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
{
    getInitialGameStateFromServer();
}

void GameManager::come_back_to_menu() { // À appeler quand la partie est terminée
    MainManager *menu_manager = new MainManager(server_ip_address, player_id, player_username, master_app);
    master_app->transition(menu_manager);
}

void *GameManager::input_thread() {

    while (1) {
        gameUI.displayPosingPhase();
        int choice = gameUI.getChoice();
        if (choice == 1) {
            gameUI.display(gameState);
            gameUI.displayTowerShop();
            int towerchoice = gameUI.getChoice();
            if (towerchoice == 1) {
                Position towerPos = gameUI.getPosBuyingTower();
                if (checkValidity(towerPos, gameState)) {
                    std::cout << "ok" << std::endl;
                    gameState.addTower(new AttackTower(Position(towerPos.getX(), towerPos.getY())));
                    sendBuyRequest(towerPos, "AttackTower");
                }
            }
            gameUI.display(gameState);
        } else if (choice == 2) {
            gameUI.display(gameState);
            Position toSell = gameUI.getPosSellingTower();
            if (isSpaceAvailableForTower(gameState, toSell)) {
                gameState.deleteTower(toSell, quadrant);
                sendSellRequest(toSell);
            }
            gameUI.display(gameState);

        }// else if upgrade tower
    }
}

bool GameManager::isSpaceAvailableForTower(GameState &gameState, Position towerPos){
    bool validity = true;
    for (auto tower : gameState.getTowers()){
        if (tower->getQuadrant() == quadrant && tower->getPosition() == towerPos){
            validity = false;
            break;
        }
    }
    return validity;
}

void *GameManager::staticInputThread(void *self){
    return static_cast<GameManager*>(self)->input_thread();
}

/*
 * checkValidity(Position towerPos, GameState& gamestate):
 * Check if the player has the money to buy a tower and if he placed it in a correct
 * position
 */
bool GameManager::checkValidity(Position towerPos, GameState& gamestate) {
    bool validity = true;
    if (gameState.getPlayerStates()[quadrant].getMoney()  < ATTACK_TOWER_PRICE) { // if player has enough money
        validity = false;
    }else if (!isSpaceAvailableForTower(gamestate, towerPos)) { // if a tower isn't already there
        validity = false;
    } else if (Map::computeQuadrant(towerPos) != quadrant) { // if the position is in the right quadrant
        validity = false;
    }
    return validity;
}


void GameManager::sendBuyRequest(Position towerPos, std::string towerType) {
    std::string message = PLACE_TOWER_COMMAND_STRING + "," + towerType + "," + std::to_string(towerPos.getX()) + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
}

void GameManager::sendSellRequest(Position towerPos) {
    std::string type = "NULL";
    std::string message = DELETE_TOWER_COMMAND_STRING + "," + type + std::to_string(towerPos.getX()) + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
}



void GameManager::run() {
    gameUI.display(gameState);
    gameUI.display(quadrant);
    gameUI.displayPlayerInfos(gameState, quadrant);
    char server_msg_buff [BUFFER_SIZE];

    while(1) {
        receive_message(server_socket, server_msg_buff);
        //std::cout << "Message: " << server_msg_buff << std::endl;
        if (strcmp(server_msg_buff, PLACING_TOWER) == 0 && is_alive()) {
            inputThread = pthread_create(&thr,NULL,&GameManager::staticInputThread,this);

        }else if (strcmp(server_msg_buff, WAVE) == 0){
            inputThread = pthread_cancel(thr);
        }
        else{
            unSerializeGameState(server_msg_buff);
            gameUI.display(gameState);
            gameUI.displayPlayerInfos(gameState, quadrant);


            if (gameState.getIsGameOver()){
                break;
            }
        }
    }

}

void GameManager::unSerializeGameState(char* seriarlized_gamestate){
    gameState = GameState();

    std::string part = "";
    unsigned count = 0; // count at which part we are
    for (char* c = seriarlized_gamestate; *c; ++c) {
        if (*c == '!') {
            switch (count) {
                case 0: // isGameOver
                    gameState.setIsGameOver(part == "true");
                    break;
                case 1: // PlayerStates
                    unSerializePlayerStates(part);
                    break;
                case 2: // Towers
                    unSerializeTowers(part);
                    break;
                default: // Waves
                    unSerializeWaves(part);
                    break;
            }
            part = "";
            count++;
        } else {
            part += *c;
        }
    }
}

void GameManager::unSerializePlayerStates(std::string serialized_playerstates) {
    std::string serialized_playerstate = "";
    for (char& c : serialized_playerstates) {
        if (c == ';') {
            unSerializePlayerState(serialized_playerstate);
            serialized_playerstate = "";
        } else {
            serialized_playerstate += c;
        }
    }
}

void GameManager::unSerializePlayerState(std::string serialized_playerstate) {
    std::string elem = "";
    unsigned count = 0;
    int player_id=0;
    int money=0;
    int hp=0;
    bool isSupported=true;
    bool isWinner=true;
    int pnjKilled=0;
    int team=0;

    for (char& c : serialized_playerstate) {
        if (c == ',') {
            switch (count) {
                case 0: // Nothing to do
                    break;
                case 1: // player_id
                    player_id = std::stoi(elem);
                    break;
                case 2: // money
                    money = std::stoi(elem);
                    break;
                case 3: // hp
                    hp = std::stoi(elem);
                    break;
                case 4: // isSupported
                    isSupported = elem == "true";
                    break;
                case 5: // isWinner
                    isWinner = elem == "true";
                    break;
                case 6: // pnjKilled
                    pnjKilled = std::stoi(elem);
                    break;
                default: // team
                    team = std::stoi(elem);
                    break;
            }
            elem = "";
            count++;
        } else {
            elem += c;
        }
    }
    PlayerState* playerState = new PlayerState(player_id, money, hp, isSupported, isWinner, pnjKilled, team);
    gameState.addPlayerState(*playerState);
}

void GameManager::unSerializeTowers(std::string serialized_towers) {
    std::string serialized_tower = "";
    for (char& c : serialized_towers) {
        if (c == ';') {
            unSerializeTower(serialized_tower);
            serialized_tower = "";
        } else {
            serialized_tower += c;
        }
    }
}

void GameManager::unSerializeTower(std::string serialized_tower) {
    std::string elem = "";
    unsigned count = 0;

    std::string typeOfTower="";
    int x=0;
    int y=0;
    for (char& c : serialized_tower) {
        if (c == ',') {
            switch (count) {
                case 0: // Type of Tower
                    typeOfTower = elem;
                    break;
                case 1: // X
                    x = std::stoi(elem);
                    break;
                default: // Y
                    y = std::stoi(elem);
                    break;
            }
            elem = "";
            count++;
        } else {
            elem += c;
        }
    }

    AbstractTower *tower;
    tower = new AttackTower(Position(x,y)); // Faire avec un if, else if, else sur typeOfTower quand + de tours

    gameState.addTower(tower);
}

void GameManager::unSerializeWaves(std::string serialized_waves) {
    std::string serialized_wave = "";
    for (char& c : serialized_waves) {
        if (c == ';') {
            unSerializeWave(serialized_wave);
            serialized_wave = "";
        } else {
            serialized_wave += c;
        }
    }
}

void GameManager::unSerializeWave(std::string serialized_wave) {
    std::string elem = "";
    bool firstElem = true;

    int quadrant=0;
    Wave *wave = new Wave(quadrant);
    for (char& c : serialized_wave) {
        if (c == '|') {
            if (firstElem) {
                quadrant = elem.back() - '0';
                wave = new Wave(quadrant);
                firstElem = false;
            } else {
                unSerializePNJ(elem, wave);
            }
            elem = "";
        } else {
            elem += c;
        }
    }
    gameState.addWave(*wave);
}

void GameManager::unSerializePNJ(std::string serialized_pnj, Wave *wave) {
    std::string elem = "";
    unsigned count = 0;

    int x=0;
    int y=0;
    int health=0;
    for (char& c : serialized_pnj) {
        if (c == ',') {
            switch (count) {
                case 0: // X
                    std::cout << elem << std::endl;
                    x = std::stoi(elem);
                    break;
                case 1:
                    std::cout << elem << std::endl;
                    y = std::stoi(elem);
                    break;
                default:
                    std::cout << elem << std::endl;
                    health = std::stoi(elem);
                    break;
            }
            elem = "";
            count++;
        } else {
            elem += c;
        }
    }
    PNJ *pnj = new PNJ(Position(x, y), health, wave->getQuadrant());
    wave->addPNJ(*pnj);
}

bool GameManager::is_alive() {
    if (gameState.getPlayerStates().size() == 0) return true;

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

    char buffer[BUFFER_SIZE];
    receive_message(server_socket, buffer);

    std::string action(buffer);
    if (action != SETUP_GAME) {
        std::cout << "Expected action was setup; it was instead " << action << std::endl;
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

void GameManager::getInitialGameStateFromServer() {
    char buffer[BUFFER_SIZE];
    receive_message(server_socket, buffer);
    unSerializeGameState(buffer);

}

