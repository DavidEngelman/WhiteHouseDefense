

#include "GameManager.hpp"
#include "GameGUI.hpp"
#include "GameConsoleUI.hpp"
#include "../../common/pnj/MexicanPNJ.h"
#include "../../common/pnj/CommunistPNJ.h"
#include "../../common/pnj/MuslimPNJ.h"
#include "../../server/Server.hpp"
#include "../../common/Command.hpp"


GameManager::GameManager(int socket, App *app) :
        AbstractManager(app),
        server_socket(socket),
        isSupporter(false)
        //gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        //quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
{
    if (!isConsole) {
        gameUI = new GameGUI(getMapSeedFromServer(), this);
    } else {
        gameUI = new GameConsoleUI(getMapSeedFromServer(),this);
    }

    quadrant = getQuadrantFromServer();

    getInitialGameStateFromServer();
}

GameManager::GameManager(int socket, bool _isSupporter, App *app) :
        AbstractManager(app),
        server_socket(socket),
        isSupporter(_isSupporter)
        //gameUI(getMapSeedFromServer()), // L'ordre est important parce qu'on fait des
        //quadrant(getQuadrantFromServer()) // recv. Ne pas changer l'ordre!
{
    if (!isConsole) {
        gameUI = new GameGUI(getMapSeedFromServer(), this);
    } else {
        gameUI = new GameConsoleUI(getMapSeedFromServer(),this);
    }

    quadrant = getQuadrantFromServer();
    getInitialGameStateFromServer();
}

void GameManager::comeBackToMenu() { // À appeler quand la partie est terminée
    MainManager *menu_manager = new MainManager(5555, master_app);
    master_app->transition(menu_manager);
}

void GameManager::updateMap() {
    char server_msg_buff[BUFFER_SIZE];
    receive_message(server_socket, server_msg_buff);

    if (strncmp(server_msg_buff, RECEIVE_MESSAGE_STRING.c_str(), RECEIVE_MESSAGE_STRING.length()) == 0) {
        Command command;
        command.parse(server_msg_buff);
        const std::string& message = command.getNextToken();
        const std::string& sender = command.getNextToken();
        gameUI->addChatMessage(message, sender);
    }
    else if (strcmp(server_msg_buff, PLACING_TOWER) == 0) {
        gameUI->disableNukeSpell();
    }

    else if (strcmp(server_msg_buff, PLACING_TOWER) != 0 && strcmp(server_msg_buff, WAVE) != 0) {
        if (nukeSpell) gameUI->enableNukeSpell();
        unSerializeGameState(server_msg_buff);
    }

    gameUI->display(gameState, quadrant);
    gameUI->displayPlayerInfos(gameState, quadrant);
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
    } else if (typeOfTower == SNIPER_TOWER_STR) {
        price = SNIPER_TOWER_PRICE;
    } else {
        price = SHOCK_TOWER_PRICE;
    }

    if (gameState.getPlayerStates()[quadrant].getMoney()  < price) { // if player has enough money
        validity = false;
    } else if (isTowerInPosition(gamestate, towerPos)) { // if a tower isn't already there
        validity = false;
    } else if (Map::computeQuadrant(towerPos) != quadrant) { // if the position is in the right quadrant
        validity = false;
    } else if (gameUI->getMap()->isPath(towerPos) || gameUI->getMap()->isObstacle(towerPos)){
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

void GameManager::sendUpgradeRequest(Position towerPos) {
    std::string type = "NULL";
    std::string message = UPGRADE_TOWER_COMMAND_STRING
                          + "," + std::to_string(quadrant)
                          + "," + type
                          + "," + std::to_string(towerPos.getX())
                          + "," + std::to_string(towerPos.getY())+";";
    send_message(server_socket, message.c_str());
}



void GameManager::run() {
    char server_msg_buff[BUFFER_SIZE];

    if (isConsole) {
        gameUI->display(gameState, quadrant);

        if (!isSupporter)
            gameUI->displayPlayerInfos(gameState, quadrant);
        else
            gameUI->displayInfoForSupporter(gameState);

        while (!gameState.getIsGameOver()) {
            receive_message(server_socket, server_msg_buff);

            //PHASE ENTRE LES WAVES
            if (strcmp(server_msg_buff, PLACING_TOWER) == 0) {

                if (is_alive() && !isSupporter) {
                    inputThread = pthread_create(&thr, NULL, &GameConsoleUI::staticInputThread, gameUI);
                } else {
                    gameUI->display(gameState, quadrant);
                    if (is_alive() && !isSupporter) {
                        inputThread = pthread_create(&thr, NULL, &GameConsoleUI::staticInputThread, gameUI);
                    } else {
                        gameUI->display(gameState, quadrant);
                    }

                    if (isSupporter) {
                        gameUI->displayPlayersPlacingTowersMessage();
                    } else {
                        gameUI->displayDeadMessage();
                    }
                }


                //DEBUT D'UNE WAVE
            } else if (strcmp(server_msg_buff, WAVE) == 0) {
                if (!isSupporter) {
                    inputThread = pthread_cancel(thr);
                }
            }
                // RECEVOIR MESSAGE DU CHAT DUN JOUEUR
            else if (strncmp(server_msg_buff, RECEIVE_MESSAGE_STRING.c_str(), RECEIVE_MESSAGE_STRING.length()) == 0) {
                Command command;
                command.parse(server_msg_buff);
                int messageLength = command.getNextInt();
                const std::string& message = command.getTokenWithSize(messageLength);
                const std::string& sender = command.getNextToken();
                gameUI->addChatMessage(message, sender);
            }

                //PHASE OU LA WAVE SE DEPLACE
            else {
                unSerializeGameState(server_msg_buff);
                gameUI->display(gameState, quadrant);

                if (!isSupporter) {
                    if (is_alive()) {
                        gameUI->displayPlayerInfos(gameState, quadrant);
                    } else {
                        gameUI->displayDeadMessage();
                    }
                } else
                    gameUI->displayInfoForSupporter(gameState);
            }
        }

        //FIN DE PARTIE
        gameUI->displayGameOver(gameState);
        // Menu to come back to main menu (or make another game of the same type ?)
        comeBackToMenu();
    } else {
        updateMap();
        //gameUI->displayTowerShop();
    }
}

void GameManager::unSerializeGameState(char* seriarlizedGamestate){
    gameState = GameState();

    std::string part = "";
    unsigned count = 0; // count at which part we are
    for (char* c = seriarlizedGamestate; *c; ++c) {
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
    int nbTowerPlaced=0;
    int damageDealt=0;
    int moneySpend=0;

    for (char& c : serialized_playerstate) {
        if (c == ',') {
            switch (count) {
                case 0: // Nothing to do
                    break;
                case 1: // playerId
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
                case 8: // team
                    team = std::stoi(elem);
                    break;
                case 9:
                    nbTowerPlaced = std::stoi(elem);
                    break;
                case 10:
                    damageDealt = std::stoi(elem);
                    break;
                default:
                    moneySpend = std::stoi(elem);
            }
            elem = "";
            count++;
        } else {
            elem += c;
        }
    }

    PlayerState* playerState = new PlayerState(player_id, username, money, hp, isSupported, isWinner,
                                               pnjKilled, team, nbTowerPlaced, damageDealt, moneySpend);
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
    int level = 0;
    for (char& c : serialized_tower) {
        if (c == ',') {
            switch (count) {
                case 0: // Type of Tower
                    typeOfTower = elem;
                    break;
                case 1: //Level of tower
                    level = stoi(elem);
                    break;
                case 2: // X
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
    Position pos = Position(x, y);

    if (typeOfTower == "GunTower") tower = new GunTower(pos, level);
    else if (typeOfTower == "SniperTower") tower = new SniperTower(pos, level);
    else tower = new ShockTower(pos, level);

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
    std::string typeOfPNJ = "";
    for (char& c : serialized_pnj) {
        if (c == ',') {
            switch (count) {
                case 0: // X
                    x = std::stoi(elem);
                    break;
                case 1:
                    y = std::stoi(elem);
                    break;
                case 2:
                    health = std::stoi(elem);
                    break;
                default:
                    typeOfPNJ = elem;
                    break;
            }
            elem = "";
            count++;
        } else {
            elem += c;
        }
    }

    PNJ *pnj;
    if (typeOfPNJ == MEXICAN_PNJ_STR) pnj = new MexicanPNJ(Position(x, y), health, wave->getQuadrant());
    else if (typeOfPNJ == MUSLIM_PNJ_STR) pnj = new MuslimPNJ(Position(x, y), health, wave->getQuadrant());
    else pnj = new CommunistPNJ(Position(x, y), health, wave->getQuadrant());

    wave->addPNJ(*pnj);
}

bool GameManager::is_alive() {
    bool gameNotInitialized = gameState.getPlayerStates().size() == 0;
    if (gameNotInitialized) return true;

    bool alive = false;
    for( PlayerState& playerState : gameState.getPlayerStates()){
        if (playerState.getPlayer_id() == master_app->getId()){
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

GameState &GameManager::getGameState() {
    return gameState;
}

int GameManager::getQuadrant() {
    return quadrant;
}

bool GameManager::placeGunTower(Position towerPos) {
    if (checkValidity(towerPos, gameState, GUN_TOWER_STR)) {
        gameState.addTower(new GunTower(Position(towerPos.getX(), towerPos.getY()), 1), quadrant);
        sendBuyRequest(towerPos, GUN_TOWER_STR);
        return true;
    }

    return false;
}

bool GameManager::placeSniperTower(Position towerPos) {
    if (checkValidity(towerPos, gameState, SNIPER_TOWER_STR)) {
        gameState.addTower(new SniperTower(Position(towerPos.getX(), towerPos.getY()),1), quadrant);
        sendBuyRequest(towerPos, SNIPER_TOWER_STR);
        return true;
    }

    return false;
}

bool GameManager::placeShockTower(Position towerPos) {
    if (checkValidity(towerPos, gameState, SHOCK_TOWER_STR)) {
        gameState.addTower(new ShockTower(Position(towerPos.getX(), towerPos.getY()),1), quadrant);
        sendBuyRequest(towerPos, SHOCK_TOWER_STR);
        return true;
    }

    return false;
}

bool GameManager::sellTower(Position toSell) {
    if (isTowerInPosition(getGameState(), toSell)) {
        gameState.deleteTower(toSell, quadrant);
        sendSellRequest(toSell);
        return true;
    }

    return false;

}

bool GameManager::upgradeTower(Position toUpgrade) {
    if (isTowerInPosition(getGameState(), toUpgrade)) {
        if (!gameState.upgradeTower(toUpgrade, quadrant))
            return false;
        sendUpgradeRequest(toUpgrade);
        return true;
    }
    return false;
}


/* In-Game Chat */

void GameManager::sendMessageToPlayers(const std::string &message) {
    // TODO: si l'utilisateur met des ; dans son message, c'est la merde
    std::string username = master_app->getUsername();
    if (isSupporter) {
        username = "[Supporter] " + username;
    }
    std::string request = SEND_MESSAGE_STRING + ","
                          + std::to_string(message.size()) + ","
                          + message + ","
                          + username + ";";
    send_message(server_socket, request.c_str());
}



/* Spells */
void GameManager::nuclearBombSpell() {
    sendNuclearRequest();
    nukeSpell = false;
    gameUI->disableNukeSpell();
}

void GameManager::sendNuclearRequest() {
    std::string message = NUCLEAR_BOMB_COMMAND_STRING
                          + "," + std::to_string(quadrant) + ";";
    send_message(server_socket, message.c_str());
}