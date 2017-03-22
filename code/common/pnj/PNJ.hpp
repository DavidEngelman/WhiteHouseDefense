

#ifndef PROJET_PNJ_H
#define PROJET_PNJ_H

#include "../Position.hpp"
#include "../Direction.hpp"
#include "../Map.hpp"
#include "../Constants.hpp"
#include "../Strings.hpp"

class Map;

class PNJ{

protected:

	int healthPoints;
	int direction;
    int damage;
	int value;
    int freezeTicksLeft;
	std::string typeOfPNJ;
	Position position;
	Position last_position;

public:


	PNJ(int direction);

    PNJ(Position position, int healthPoints, int direction);

    PNJ(Position position, int healthPoints, Position last_pos, int direction);

    virtual ~PNJ() = 0;

	void advance(Map& map);

	int getHealthPoints() const;

	int receiveDamage(int damageAmount);

	bool isDead();

	void setHealthPoints(int newHp);

	bool isInPlayerBase();

	Position getPosition() const;

    const std::string& getType();

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

    int getDamage();

	int getValue();

    bool operator==(const PNJ &rhs) const;

    bool operator!=(const PNJ &rhs) const;

    Direction get_random_direction();

    Direction get_backward_direction();

	bool can_go_backward(Map &map);

	void freeze();
};

inline PNJ::~PNJ(){}

#endif // PROJET_PNJ_H
