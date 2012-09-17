#include "Position.h"


Position::Position(int x, int y)
{
	this->setType(POSITION);
	this->x = x;
	this->y = y;
}


Position::~Position(void)
{
}

void Position::setX(int x) {
	this->x = x;
}

void Position::setY(int y) {
	this->y = y;
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}
