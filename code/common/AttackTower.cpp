#include "AttackTower.hpp"

AttackTower::AttackTower(Position position, int damage, int price, float range) :
        AbstractTower::AbstractTower(position, price, range), damage(damage) {}

int AttackTower::getDamageAmount() const { return level*damage/10 + damage; } // +10% d'attaque par upgrade

void AttackTower::dealDamageTo(PNJ &target) { target.receiveDamage(this->getDamageAmount()); }