#include "PlayerState.hpp"

PlayerState::PlayerState() : money(STARTING_MONEY), hp(STARTING_HP), isSupported(false), pnjKilled(0) {}

PlayerState::PlayerState(int id) : PlayerState(id, -1) {}

PlayerState::PlayerState(int id, int team) : player_id(id), team(team), hp(STARTING_HP), money(STARTING_MONEY),
                                             pnjKilled(0) {}
PlayerState::PlayerState(int _player_id, int _money, int _hp, bool _isSupported, bool _isWinner, int _pnjKilled,
                         int _team) : player_id(_player_id), money(_money), hp(_hp), isSupported(_isSupported),
                                      isWinner(_isWinner), pnjKilled(_pnjKilled), team(_team){}

std::string PlayerState::bool_to_string(bool my_bool){
    return my_bool ? "true" : "false";
}


int PlayerState::getHp(){
    return hp;
}

std::string PlayerState::serialize() {
    /*
     * fill a string like this : PlayerState,player_quadrant,money,hp,isSupported,isWinner,pnjKilled,team;
     */

    std::string serialized_me;
    serialized_me += "PlayerState," + std::to_string(player_id) + "," + std::to_string(money) + "," +
            std::to_string(hp) + "," + bool_to_string(isSupported)+
            "," + bool_to_string(isWinner) + "," + std::to_string(pnjKilled) + "," + std::to_string(team) + ";";

    return serialized_me;
}

void PlayerState::setHp(int newHp){
    hp = newHp;
}

int PlayerState::getMoney(){
    return money;
}

void PlayerState::earnMoney(int amount){
    money += amount;
}

bool PlayerState::getIsSupported(){
    return isSupported;
}

void PlayerState::setIsSupported(bool isSupported){
    isSupported = isSupported;
}

bool PlayerState::getIsWinner(){
    return isWinner;
}

void PlayerState::setIsWinner(bool newValue){
    isWinner = newValue;
}

int PlayerState::getPlayer_id(){
    return player_id;
}

void PlayerState::setPlayer_id(int newId){
    player_id = newId;
}

void PlayerState::spendMoney(int amount){
    money -= amount;
}

void PlayerState::decrease_hp(int amount) {
    setHp(getHp() - amount);
}

void PlayerState::increase_hp(int amount) {
    setHp(getHp() + amount);
}

int PlayerState::getTeam() {
    return team;
}

int PlayerState::getPnjKilled() const {
    return pnjKilled;
}

void PlayerState::addOneKill() {
    pnjKilled += 1;
}

void PlayerState::setTeam(int teamNumber) {
    team = teamNumber;
}

bool PlayerState::isAlive() {
    return hp > 0;
}
