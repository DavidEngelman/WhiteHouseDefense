#include "AttackTower.hpp"

int AttackTower::getDamageAmount() const { return damageAmount; }

void AttackTower::setDamageAmount(int damageAmount) { this->damageAmount = damageAmount; }

void AttackTower::shoot(PNJ target) { this->dealDamageTo(target); }

void AttackTower::dealDamageTo(PNJ target) { target.receiveDamage(this->getDamageAmount()); }