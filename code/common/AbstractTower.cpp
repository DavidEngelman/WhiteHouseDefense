#include "AbstractTower.hpp"

AbstractTower::AbstractTower(Position position, int price, int owner, int radius):
        position(position), price(price), owner(owner), radius(owner) {}

AbstractTower::~AbstractTower() {}

int AbstractTower::getOwner() const { return owner; }

void AbstractTower::setOwner(int owner) { this->owner = owner; }

const int AbstractTower::getPrice() const { return price; }

int AbstractTower::getRadius() const { return radius; }

void AbstractTower::setRadius(int radius) { this->radius = radius; }

Position AbstractTower::getPosition() const { return position; }

void AbstractTower::setPosition(Position position) { this->position = position; }

std::string AbstractTower::serialize() {

    std::string serialized_me;

    serialized_me += std::to_string(owner) + "," + std::to_string(price) + "," +
                     std::to_string(radius) + ","/* + TODO:position.serialize()*/ + ";";

    return serialized_me;
}
