#pragma once
#include "Unit.h"

class Position : public Unit
{
public:
	Position(int x, int y);
	~Position(void);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

private:
	int x;
	int y;
};

