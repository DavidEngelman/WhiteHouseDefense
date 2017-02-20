#include "AttackTower.hpp"

AttackTower::AttackTower(int damageAmount): damageAmount(damageAmount) {}

int AttackTower::getDamageAmount() const { return damageAmount; }

void AttackTower::setDamageAmount(int damageAmount) { this->damageAmount = damageAmount; }

void AttackTower::shoot(PNJ target) { this->dealDamageTo(target); }

void AttackTower::dealDamageTo(PNJ target) { target.receiveDamage(this->getDamageAmount()); }

std::string AttackTower::serialize() {
    /*
     * Une AttackTower sérialisée est comme ceci : "AttackTower,damageAmount,owner,price,radius,position;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, "AttackTower,");

    return serialized_me;


}