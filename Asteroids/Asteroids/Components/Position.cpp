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

sf::Packet Position::getPacket() {
	sf::Packet packet;
	return packet;
}

void Position::refresh(sf::Packet packet) {
}

void Position::rotateLeft() {
	--(this->rotation);
}

void Position::rotateRight() {
	++(this->rotation);
}

int Position::getRotation() {
	return (this->rotation)%360;
}