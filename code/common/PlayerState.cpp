#include "PlayerState.hpp"

int PlayerState::getHp(){
    return hp;
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

void PlayerState::getAccount(){
    //TODO: utile ?
}

void PlayerState::setAccount(int account){
    //TODO: utile ?
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