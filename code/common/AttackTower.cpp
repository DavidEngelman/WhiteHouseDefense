#include "AttackTower.hpp"

AttackTower::AttackTower(Position position) :
        AbstractTower::AbstractTower(position, ATTACK_TOWER_PRICE, ATTACK_TOWER_RANGE) {}

int AttackTower::getDamageAmount() const { return level*ATTACK_TOWER_DAMAGE/10 + ATTACK_TOWER_DAMAGE; } // +10% d'attaque par upgrade

bool AttackTower::shoot(Wave &wave) {
    PNJ *my_target;
    bool killed = false;
    my_target = get_closest_pnj(wave);
    if ( (my_target != nullptr) && (!my_target->isInPlayerBase()) && (my_target->getHealthPoints() > 0) ) {
        dealDamageTo(*my_target);
        if (my_target->getHealthPoints() <= 0) {
            killed = true;
        }
    }
    return killed;
}

void AttackTower::dealDamageTo(PNJ &target) { target.receiveDamage(this->getDamageAmount()); }

std::string AttackTower::serialize() {
    /*
     * Une AttackTower sérialisée est comme ceci : "AttackTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, "AttackTower");

    return serialized_me;


}
