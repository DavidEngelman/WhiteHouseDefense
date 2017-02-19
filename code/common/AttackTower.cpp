#include "AttackTower.hpp"

int AttackTower::getDamageAmount() const { return damageAmount; }

void AttackTower::setDamageAmount(int damageAmount) { this->damageAmount = damageAmount; }

virtual void AttackTower::dealDamageTo(PNJ pnj) { pnj.receiveDamage(this->getDamageAmount()); }