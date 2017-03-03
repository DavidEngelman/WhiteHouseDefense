

#include "GameManager.hpp"
#include "../server/Server.hpp"


GameManager::GameManager(int socket, App *app) :
        AbstractManager(app),
        server_socket(socket),
        isSupporter(false),
        gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
{
    getInitialGameStateFromServer();
}

GameManager::GameManager(int socket, bool _isSupporter, App *app) :
        AbstractManager(app),
        server_socket(socket),
        isSupporter(_isSupporter),
        gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
{
    getInitialGameStateFromServer();
}

void GameManager::come_back_to_menu() { // À appeler quand la partie est terminée
    MainManager *menu_manager = new MainManager(5555, master_app);
    master_app->transition(menu_manager);
}

void *GameManager::input_thread() {
    //TODO: diviser cette méthode en plusieurs plus petites pcq la c'est pas très lisible

    while (1) {
        gameUI.displayPosingPhase();
        int choice = gameUI.getChoice();
        gameUI.display(gameState, quadrant);
        gameUI.displayPlayerInfos(gameState, quadrant);
        if (choice == 1) {
            gameUI.displayTowerShop();
            int towerchoice = gameUI.getChoice();
            gameUI.display(gameState, quadrant);
            gameUI.displayPlayerInfos(gameState, quadrant);
            Position towerPos = gameUI.getPosBuyingTower();
            if (towerchoice == 1) {
                if (checkValidity(towerPos, gameState, GUN_TOWER_STR)) {
                    gameState.addTower(new GunTower(Position(towerPos.getX(), towerPos.getY())), quadrant);
                    sendBuyRequest(towerPos, GUN_TOWER_STR);
                }
            } else {
                gameState.addTower(new SniperTower(Position(towerPos.getX(), towerPos.getY())), quadrant);
                sendBuyRequest(towerPos, SNIPER_TOWER_STR);
            }
        }else if (choice == 2){
            Position toSell = gameUI.getPosSellingTower();
            if (isTowerInPosition(gameState, toSell)){
                gameState.deleteTower(toSell, quadrant);
                sendSellRequest(toSell);
            }
        }// else upgrade tower
        gameUI.display(gameState, quadrant);
        gameUI.displayPlayerInfos(gameState, quadrant);
    }
}

bool GameManager::isTowerInPosition(GameState &gameState, Position towerPos){
    bool validity = false;
    for (auto tower : gameState.getTowers()){
        if (tower->getQuadrant() == quadrant && tower->getPosition() == towerPos){
            validity = true;
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
bool GameManager::checkValidity(Position towerPos, GameState& gamestate, std::string typeOfTower) {
    bool validity = true;
    int price;

    if (typeOfTower == GUN_TOWER_STR) {
        price = GUN_TOWER_PRICE;
    } else {
        price = SNIPER_TOWER_PRICE;
    }

    if (gameState.getPlayerStates()[quadrant].getMoney()  < price) { // if player has enough money
        validity = false;
    } else if (isTowerInPosition(gamestate, towerPos)) { // if a tower isn't already there
        validity = false;
    } else if (Map::computeQuadrant(towerPos) != quadrant) { // if the position is in the right quadrant
        validity = false;
    } else if (gameUI.getMap()->isPath(towerPos)){
        validity = false;
    }
    return validity;
}


void GameManager::sendBuyRequest(Position towerPos, std::string towerType) {
    std::string message = PLACE_TOWER_COMMAND_STRING
                          + "," + std::to_string(quadrant)
                          + "," + towerType
                          + "," + std::to_string(towerPos.getX())
                          + "," + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
}

void GameManager::sendSellRequest(Position towerPos) {
    std::string type = "NULL";
    std::string message = DELETE_TOWER_COMMAND_STRING
                          + "," + std::to_string(quadrant)
                          + "," + type
                          + "," + std::to_string(towerPos.getX())
                          + "," + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
}



void GameManager::run() {
    gameUI.display(gameState, quadrant);
    gameUI.displayPlayerInfos(gameState, quadrant);
    char server_msg_buff [BUFFER_SIZE];

    while(!gameState.getIsGameOver()) {
        receive_message(server_socket, server_msg_buff);
        //std::cout << "Message: " << server_msg_buff << std::endl;
        if (strcmp(server_msg_buff, PLACING_TOWER) == 0) {

            if (is_alive() && !isSupporter ) {
                inputThread = pthread_create(&thr, NULL, &GameManager::staticInputThread, this);
            } else {
                gameUI.display(gameState, quadrant);

                if (isSupporter) {
                    gameUI.displayPlayersPlacingTowersMessage();
                } else {
                    gameUI.display_dead_message();
                }
            }
        }else if (strcmp(server_msg_buff, WAVE) == 0){
            if (!isSupporter) {
                inputThread = pthread_cancel(thr);
            }
        }
        else {
            unSerializeGameState(server_msg_buff);
            gameUI.display(gameState, quadrant);

            if (!isSupporter) {
                if (is_alive()) {
                    gameUI.displayPlayerInfos(gameState, quadrant);
                } else {
                    gameUI.display_dead_message();
                }
            } else
                gameUI.displayInfoForSupporter(gameState);
        }
    }
    gameUI.displayGameOver(gameState);

    // Menu to come back to main menu (or make another game of the same type ?)
    come_back_to_menu();

}

void GameManager::unSerializeGameState(char* seriarlized_gamestate){
    gameState = GameState();

    std::string part = "";
    unsigned count = 0; // count at which part we are
    for (char* c = seriarlized_gamestate; *c; ++c) {
        if (*c == '!') {
            switch (count) {
                case 0: // isGameOver
                    gameState.setGameMode(part);
                    break;
                case 1: // isGameOver
                    gameState.setIsGameOver(part == "true");
                    break;
                case 2: // PlayerStates
                    unSerializePlayerStates(part);
                    break;
                case 3: // Towers
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
            unSerializePlayerState(serialized_playerstate + ",");
            serialized_playerstate = "";
        } else {
            serialized_playerstate += c;
        }
    }
}

void GameManager::unSerializePlayerState(std::string serialized_playerstate) {
    std::string elem = "";
    unsigned count = 0;
    std::string username;
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
                case 2:
                    username = elem;
                    break;
                case 3: // money
                    money = std::stoi(elem);
                    break;
                case 4: // hp
                    hp = std::stoi(elem);
                    break;
                case 5: // isSupported
                    isSupported = elem == "true";
                    break;
                case 6: // isWinner
                    isWinner = elem == "true";
                    break;
                case 7: // pnjKilled
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
    PlayerState* playerState = new PlayerState(player_id, username, money, hp, isSupported, isWinner,
                                               pnjKilled, team);
    gameState.addPlayerState(*playerState);
}

void GameManager::unSerializeTowers(std::string serialized_towers) {
    std::string serialized_tower = "";
    for (char& c : serialized_towers) {
        if (c == ';') {
            unSerializeTower(serialized_tower + ",");
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
                default:
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
    if (typeOfTower == "GunTower") tower = new GunTower(Position(x, y));
    else tower = new SniperTower(Position(x, y));
    //TODO: remplacer par gameState.addTower(tower)
    //Pour ne pas utiliser un getter pour modifier la classe, ça n'a aucun sens
    gameState.getTowers().push_back(tower);
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
                unSerializePNJ(elem + ",", wave);
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
                    x = std::stoi(elem);
                    break;
                case 1:
                    y = std::stoi(elem);
                    break;
                default:
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
    bool gameNotInitialized = gameState.getPlayerStates().size() == 0;
    if (gameNotInitialized) return true;

    bool alive = false;
    for( PlayerState& playerState : gameState.getPlayerStates()){
        if (playerState.getPlayer_id() == master_app->get_id()){
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


void GameManager::getInitialGameStateFromServer() {
    char buffer[BUFFER_SIZE];
    receive_message(server_socket, buffer);
    unSerializeGameState(buffer);
}

