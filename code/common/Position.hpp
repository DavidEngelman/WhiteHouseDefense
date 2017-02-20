#ifndef __POSITION__
#define __POSITION__
class Position { // There is already a struct in the map class

private:

	int x;
	int y;

public:

    Position(int x, int y);

	int getX();

	void setX(int x);

	int getY();

	void setY(int y);
};

#endif
