#include "PlayerState.hpp"

int PlayerState::getHp(){
    return hp;
}

std::string PlayerState::serialize() {
    //TODO
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

void PlayerState::getIsSupported(){
    return isSupported;
}

void PlayerState::setIsSupported(bool isSupported){
    isSupported = isSupported;
}

void PlayerState::getIsWinner(){
    return isWinner;
}

void PlayerState::setIsWinner(bool newValue){
    isWinner = newValue;
}

void PlayerState::getPlayer_id(){
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

void PlayerState::decrease_hp(int amount) {
    setHp(getHp() + amount);
}