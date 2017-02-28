

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

void GameManager::come_back_to_menu() {
    MainManager *menu_manager = new MainManager(server_ip_address, player_id, player_username, master_app);
    master_app->transition(menu_manager);

}

void *GameManager::input_thread() {
    //runningThread = true;
    pthread_cond_t dummy;
    pthread_mutex_t mutex;

    std::cout << "1. Buy tower " << std::endl;
    std::cout << "2. Sell tower " << std::endl;
    std::cout << "3. Upgrade tower " << std::endl;
    std::cout << std::endl;

    std::cout << "Your choice :   ";
    std::string choice;
    std::cin >> choice;
    if (choice == "1") {
        gameUI.display(gameState);
        std::cout << "1. Attacktower " << std::endl;
        std::cout << "Your choice :   ";
        std::string towerChoice;
        std::cin >> towerChoice;
        if (choice == "1") {
            Position towerPos = gameUI.getPosBuyingTower();
            if (checkValidity(towerPos)) {
                gameState.addTower(new AttackTower(Position(towerPos.getX(), towerPos.getY())));
            }
        }
        gameUI.display(gameState);
    }
    //runningThread = false;
    pthread_cond_wait(&dummy, &mutex);

}

void *GameManager::staticInputThread(void *self){
    return static_cast<GameManager*>(self)->input_thread();
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
    gameUI.display(gameState);
    gameUI.display(quadrant);
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

