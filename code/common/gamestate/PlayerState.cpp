#include "PlayerState.hpp"
#include "../Tools.hpp"

PlayerState::PlayerState() : money(PLAYER_STARTING_MONEY), hp(PLAYER_STARTING_HP), isSupported(false), NPCKilled(0) {}

PlayerState::PlayerState(int id, std::string username) : PlayerState(id, username, -1) {}

PlayerState::PlayerState(int id, std::string username, int team)
        : player_id(id), username(username), team(team), isSupported(false),
          isWinner(false), hp(PLAYER_STARTING_HP), money(PLAYER_STARTING_MONEY), NPCKilled(0), nbTowersPlaced(0),
          damageDealt(0), moneySpend(0) {}

PlayerState::PlayerState(int _player_id, std::string _username, int _money, int _hp, bool _isSupported,
                         bool _isWinner, int _pnjKilled, int _team, int _nbTowerPlaced, int _damageDealt, int _moneySpend )
        : player_id(_player_id), username(_username), money(_money), hp(_hp), isSupported(_isSupported),
          isWinner(_isWinner), NPCKilled(_pnjKilled), team(_team), nbTowersPlaced(_nbTowerPlaced),
          damageDealt(_damageDealt), moneySpend(_moneySpend) {}

int PlayerState::getHp() {
    return hp;
}

std::string PlayerState::serialize() {
    /*
     * fill a string like this : PlayerState,player_quadrant,money,hp,isSupported,isWinner,pnjKilled,team;
     */

    std::string serialized_me;
    serialized_me += "PlayerState,"
                     + std::to_string(player_id) + ","
                     + username + ","
                     + std::to_string(money) + ","
                     + std::to_string(hp) + ","
                     + bool_to_string(isSupported) + ","
                     + bool_to_string(isWinner) + ","
                     + std::to_string(NPCKilled) + ","
                     + std::to_string(team) + ","
                     + std::to_string(nbTowersPlaced) + ","
                     + std::to_string(damageDealt) + ","
                     + std::to_string(moneySpend) +";";


    return serialized_me;
}

void PlayerState::setHp(int newHp) {
    hp = newHp;
}

int PlayerState::getMoney() {
    return money;
}

void PlayerState::earnMoney(int amount) {
    money += amount;
}

bool PlayerState::getIsSupported() {
    return isSupported;
}

void PlayerState::setIsSupported(bool _isSupported) {
    isSupported = _isSupported;
}

bool PlayerState::getIsWinner() {
    return isWinner;
}

void PlayerState::setIsWinner(bool newValue) {
    isWinner = newValue;
}

int PlayerState::getPlayer_id() {
    return player_id;
}

void PlayerState::spendMoney(int amount) {
    money -= amount;
}

void PlayerState::decrease_hp(int amount) {
    if (getHp() < amount){
        setHp(0);
    } else {
        setHp(getHp() - amount);
    }
}

void PlayerState::increase_hp(int amount) {
    setHp(getHp() + amount);
}

int PlayerState::getTeam() {
    return team;
}

int PlayerState::getPnjKilled() const {
    return NPCKilled;
}

void PlayerState::addOneKill() {
    NPCKilled += 1;
}

void PlayerState::setTeam(int teamNumber) {
    team = teamNumber;
}

bool PlayerState::isAlive() {
    return hp > 0;
}

std::string &PlayerState::getUsername() {
    return username;
}

void PlayerState::incrNbTowerPlaced() {
    nbTowersPlaced ++;
}

void PlayerState::incrDamageDealt(int amount) {
    PlayerState::damageDealt += amount;
}

void PlayerState::incrMoneySpend(int amount) {
    PlayerState::moneySpend += amount;
}

int PlayerState::getNPCKilled() const {
    return NPCKilled ;
}

int PlayerState::getNbTowersPlaced() const {
    return nbTowersPlaced ;
}

int PlayerState::getDamageDealt() const {
    return damageDealt ;
}

int PlayerState::getMoneySpend() const {
    return moneySpend ;
}
