#include "AttackTower.hpp"

AttackTower::AttackTower(Position position, int damage, int price, float range, int level) :
        AbstractTower::AbstractTower(position, price, range, level ), damage(damage) {}

int AttackTower::getDamageAmount() const { return level*damage/10 + damage; } // +10% d'attaque par upgrade

void AttackTower::dealDamageTo(PNJ &target) { target.receiveDamage(this->getDamageAmount()); }