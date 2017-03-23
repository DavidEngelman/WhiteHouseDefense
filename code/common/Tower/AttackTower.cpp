#include <iostream>
#include "AttackTower.hpp"

AttackTower::AttackTower(Position position, int damage, int price, float range, int level) :
        AbstractTower::AbstractTower(position, price, range, level ), damage(damage) {}

int AttackTower::getDamageAmount() const { return level*damage/10 + damage; } // +10% d'attaque par upgrade

void AttackTower::dealDamageTo(PNJ &target, PlayerState& playerState) {
    int damage = std::min(target.getHealthPoints(), this->getDamageAmount());
    target.receiveDamage(damage);
    playerState.incrDamageDealt(damage);
}

AttackTower::AttackTower(int damage) : AbstractTower(Position(0, 0), 0, 0, 0), damage(damage) {}
