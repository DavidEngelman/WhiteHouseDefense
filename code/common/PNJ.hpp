

#ifndef PROJET_PNJ_H
#define PROJET_PNJ_H

#include "Position.hpp"
#include "Direction.h"
#include "Map.hpp"
#include "Constants.h"

class PNJ{

private:

	int healthPoints;
	int direction;
	int movementSpeed;
	Position position;
	Position last_position;

public:

	PNJ(int direction);

    PNJ(Position position, int healthPoints, int movementSpeed, Position last_pos, int direction);

    ~PNJ() = default;

	void advance(Map& map);

	int getHealthPoints() const;

	void receiveDamage(int damageAmount);

	bool isDead();

	int getMovementSpeed() const;

	void setMovementSpeed(int newMovementSpeed);

    void receiveMovementPenalty(int speedReduction);

	Position getPosition() const;

	void setPosition(Position position);


	bool can_go_forward(Map &map);

	bool can_go_left(Map &map);

	bool can_go_right(Map &map);

	Direction get_forward_direction();

	Direction get_right_direction();

	Direction get_left_direction();

    int getDirection() const;

    const Position &getLast_position() const;

    void setLast_position(const Position &last_position);

	std::string serialize();


    bool operator==(const PNJ &rhs) const;

    bool operator!=(const PNJ &rhs) const;
};

#endif // PROJET_PNJ_H
